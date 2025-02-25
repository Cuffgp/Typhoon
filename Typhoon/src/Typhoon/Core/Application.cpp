#include "typch.h"

#include "Typhoon/Core/Application.h"

namespace Typhoon {

	Application::Application()
	{
		TY_INFO("Creating application");

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();
		}
	}

}