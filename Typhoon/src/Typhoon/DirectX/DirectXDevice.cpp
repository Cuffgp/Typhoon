#include "typch.h"

#include "DirectXDevice.h"


namespace Typhoon {

	DirectXDevice::DirectXDevice()
	{
		// Setup the debug layer
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&m_DebugController))))
		{
			m_DebugController->EnableDebugLayer();
			m_DebugController->SetEnableGPUBasedValidation(TRUE);
			TY_INFO("D3D12 Debug Layer enabled.");
		}
		else
		{
			TY_ERROR("Failed to enable D3D12 Debug Layer.");
		}

		// Create the factory, adaptor, and device
		auto hr = CreateDXGIFactory1(IID_PPV_ARGS(&m_Factory));

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

		// Query the debug device from the D3D12 device
		if (SUCCEEDED(m_Device->QueryInterface(IID_PPV_ARGS(&m_DebugDevice))))
		{
			TY_INFO("D3D12 Debug Device acquired.");
		}
		else
		{
			TY_ERROR("Failed to acquire D3D12 Debug Device.");
		}

		if (SUCCEEDED(m_DebugDevice->QueryInterface(IID_PPV_ARGS(&m_InfoQueue))))
		{
			TY_INFO("Info Queue Created.");
		}
		else
		{
			TY_ERROR("Failed to create info queue");
		}

		
	}

	DirectXDevice::~DirectXDevice()
	{
		if (m_Validation)
		{
			m_DebugController->Release();
			m_DebugDevice->ReportLiveDeviceObjects(D3D12_RLDO_SUMMARY);
			m_DebugDevice->Release();
			m_InfoQueue->Release();
		}

		m_Device->Release();
		m_Adapter->Release();
		m_Factory->Release();
	}

	void DirectXDevice::RetrieveDebugMsg()
	{
		for (size_t index = 0; index < m_InfoQueue->GetNumStoredMessages(); index++)
		{
			size_t length;
			D3D12_MESSAGE message;
			m_InfoQueue->GetMessage(index, &message, &length);

			auto category = message.Severity;
			auto severity = message.Severity;

			if (severity == D3D12_MESSAGE_SEVERITY_INFO)
				TY_INFO("DirectX: {}", message.pDescription);
			else if (category == D3D12_MESSAGE_SEVERITY_WARNING)
				TY_WARN("DirectX: {}", message.pDescription);
			else if (category == D3D12_MESSAGE_SEVERITY_ERROR)
				TY_ERROR("DirectX: {}", message.pDescription);
			else if (category == D3D12_MESSAGE_SEVERITY_CORRUPTION)
				TY_ERROR("DirectX: {}", message.pDescription);
			else
				TY_TRACE("DirectX: {}", message.pDescription);
		}

		m_InfoQueue->ClearStoredMessages();
	}

}