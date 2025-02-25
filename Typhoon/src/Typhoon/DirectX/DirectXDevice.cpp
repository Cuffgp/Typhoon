#include "typch.h"

#include "Typhoon/DirectX/DirectXDevice.h"


namespace Typhoon {

	DirectXDevice* DirectXDevice::s_Device = nullptr;

	static void DebugMessageCallback(
		D3D12_MESSAGE_CATEGORY Category,
		D3D12_MESSAGE_SEVERITY Severity,
		D3D12_MESSAGE_ID ID,
		LPCSTR pDescription,
		void* pContext)
	{
		// Handle the debug message here
		// You can log it, print it, or take other actions based on the severity/category
		TY_INFO("Debug Message: {}", pDescription);
	}

	DirectXDevice::DirectXDevice()
	{
		uint32_t dxgiFactoryFlags = 0;

		if (m_Validation)
		{
			if (D3D12GetDebugInterface(IID_PPV_ARGS(&m_DebugController)) != S_OK)
			{
				TY_ERROR("Failed to create Debug interface");
			}

			m_DebugController->EnableDebugLayer();
			m_DebugController->SetEnableGPUBasedValidation(true);
			//m_DebugController->QueryInterface(IID_PPV_ARGS(&m_InfoQueue));

			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}

		// Create the factory, adaptor, and device
		auto hr = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_Factory));

		uint32_t adapterCount = 0;
		IDXGIAdapter1* adapter;

		while (m_Factory->EnumAdapters1(adapterCount, &adapter) != DXGI_ERROR_NOT_FOUND)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);

			TY_INFO(L"Physical Device: {}", desc.Description);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				adapter->Release();
				continue;
			}

			hr = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_Device));

			if (SUCCEEDED(hr))
			{
				TY_INFO(L"Selecting Device {}", desc.Description);
				TY_INFO("Memory: {} MB Dedicated, {} MB Shared", desc.DedicatedVideoMemory / (1024 * 1024),
					desc.SharedSystemMemory / (1024 * 1024));
				m_Adapter = adapter;
				break;
			}

			adapter->Release();
			++adapterCount;
		}

		if (m_Adapter == nullptr)
		{
			TY_ERROR("Failed to select adapter");
		}

		m_Device->QueryInterface(IID_PPV_ARGS(&m_InfoQueue));

		DWORD callbackCookie;
		D3D12_MESSAGE_CALLBACK_FLAGS callbackFlags = D3D12_MESSAGE_CALLBACK_FLAG_NONE;
		m_InfoQueue->RegisterMessageCallback(DebugMessageCallback, callbackFlags, nullptr, &callbackCookie);

		//RetrieveDebugMsg();

		
	}

	DirectXDevice::~DirectXDevice()
	{

		m_Device->Release();
		m_Adapter->Release();
		m_Factory->Release();

		if (m_Validation)
		{
			m_DebugController->Release();
			//m_DebugDevice->ReportLiveDeviceObjects(D3D12_RLDO_SUMMARY);
			//m_DebugDevice->Release();
			m_InfoQueue->Release();
		}
	}

	void DirectXDevice::Init()
	{
		s_Device = new DirectXDevice();
	}

	void DirectXDevice::Destroy()
	{
		delete s_Device;
		s_Device = nullptr;
	}

	void DirectXDevice::RetrieveDebugMsg()
	{
		for (size_t index = 0; index < m_InfoQueue->GetNumStoredMessages(); index++)
		{
			size_t length = 0;
			std::vector<byte> messageData;

			m_InfoQueue->GetMessage(index, nullptr, &length);
			messageData.resize(length);
			D3D12_MESSAGE* message = reinterpret_cast<D3D12_MESSAGE*>(messageData.data());
			m_InfoQueue->GetMessage(index, message, &length);
			
			auto category = message->Category;
			auto severity = message->Severity;
			
			if (severity == D3D12_MESSAGE_SEVERITY_INFO)
				TY_INFO("[DirectX] {}", message->pDescription);
			else if (category == D3D12_MESSAGE_SEVERITY_WARNING)
				TY_WARN("[DirectX] {}", message->pDescription);
			else if (category == D3D12_MESSAGE_SEVERITY_ERROR)
				TY_ERROR("[DirectX] {}", message->pDescription);
			else if (category == D3D12_MESSAGE_SEVERITY_CORRUPTION)
				TY_ERROR("[DirectX] {}", message->pDescription);
			else
				TY_TRACE("[DirectX] {}", message->pDescription);
				
		}

		m_InfoQueue->ClearStoredMessages();
	}

}