#include "typch.h"
#include "vulkan/vulkan.h"
#include <iostream>

#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

int main ()
{
	spdlog::info("Hello world");

	if (!glfwInit())
	{
		spdlog::info("Failed to init GLFW");
		return -1;
	}

	GLFWwindow* window;

	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		spdlog::info("Failed to create window");
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}