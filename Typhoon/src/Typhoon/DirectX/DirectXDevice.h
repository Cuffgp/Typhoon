#pragma once

// DirectX 12 specific headers.
#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>

// D3D12 extension library.
//#include <d3dx12/d3dx12.h>


namespace Typhoon {

	class DirectXDevice
	{
	public:
		DirectXDevice();
		~DirectXDevice();

		void RetrieveDebugMsg();
	private:
		bool m_Validation = true;

		ID3D12Debug1* m_DebugController = nullptr;
		ID3D12DebugDevice* m_DebugDevice = nullptr;
		ID3D12InfoQueue* m_InfoQueue = nullptr;

		IDXGIFactory6* m_Factory = nullptr;
		IDXGIAdapter1* m_Adapter = nullptr;
		ID3D12Device* m_Device = nullptr;
	};

}