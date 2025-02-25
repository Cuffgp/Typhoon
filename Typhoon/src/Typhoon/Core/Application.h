#pragma once

#include "Typhoon/Core/Base.h"
#include "Typhoon/Core/Window.h"
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
		Scope<Window> m_Window;

	};


}