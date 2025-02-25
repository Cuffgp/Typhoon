#include "typch.h"

#include "Typhoon/Core/Window.h"

namespace Typhoon {

	void ErrorCallback(int error, const char* description)
	{
		TY_ERROR("GLFW: {}", description);
	}

	Window::Window(uint32_t width, uint32_t height, std::string title) :
		m_Width(width), m_Height(height), m_Title(title)
	{
		if (!glfwInit())
		{
			TY_INFO("Failed to init GLFW");
		}

		glfwSetErrorCallback(ErrorCallback);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			TY_INFO("Failed to create window");
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

}
