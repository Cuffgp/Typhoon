#pragma once

#include "glfw/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw/include/GLFW/glfw3native.h"

namespace Typhoon {

	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, std::string title);
		~Window();

		bool ShouldClose() { return glfwWindowShouldClose(m_Window); }
		void PollEvents() { glfwPollEvents(); }

		GLFWwindow* GetWindowPointer() { return m_Window; }
		HWND GetRawWindowPointer() { return glfwGetWin32Window(m_Window); }
		uint32_t Width() { return m_Width; }
		uint32_t Height() { return m_Height; }
	private:
		GLFWwindow* m_Window;
		uint32_t m_Width;
		uint32_t m_Height;
		std::string m_Title;
	};

}

