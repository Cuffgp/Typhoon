#include "typch.h"

#include "Application.h"

namespace Typhoon {

	Application::Application()
	{
		SPDLOG_INFO("Creating application");

		if (!glfwInit())
		{
			SPDLOG_INFO("Failed to init GLFW");
		}

		m_Window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			SPDLOG_INFO("Failed to create window");
		}

		m_Device = new VulkanDevice();

	}

	Application::~Application()
	{
		delete m_Device;

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