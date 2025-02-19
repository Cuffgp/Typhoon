#include "typch.h"

#include "Log.h"

#include "vulkan/vulkan.h"
#include <iostream>

#include "Application.h"

int main ()
{
	Typhoon::Application *app = new Typhoon::Application;

	app->Run();

	delete app;

	return 0;

}