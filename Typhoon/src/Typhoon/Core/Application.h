#pragma once

#include "Typhoon/Core/Base.h"
#include "Typhoon/DirectX/DirectXDevice.h"

#include "glfw/glfw3.h"

namespace Typhoon {

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
	private:
		GLFWwindow* m_Window;
		Scope<DirectXDevice> m_Device;

	};


}