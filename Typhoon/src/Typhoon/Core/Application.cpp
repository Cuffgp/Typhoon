#include "typch.h"

#include "Typhoon/Core/Application.h"

namespace Typhoon {

	Application::Application()
	{
		TY_INFO("Creating application");

		if (!glfwInit())
		{
			TY_INFO("Failed to init GLFW");
		}

		m_Window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			TY_INFO("Failed to create window");
		}

		m_Device = CreateScope<DirectXDevice>();
	}

	Application::~Application()
	{

		glfwTerminate();
	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();
		}
	}

}