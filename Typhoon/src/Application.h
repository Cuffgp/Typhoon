#pragma once

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

	};


}