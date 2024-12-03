#include "typch.h"
#include "vulkan/vulkan.h"
#include <iostream>

#include "GLFW/glfw3.h"

int main ()
{
	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window;

	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}