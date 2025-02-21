#include "typch.h"

#include "Typhoon/Core/Log.h"

#include "Typhoon/Core/Application.h"

int main ()
{
	Typhoon::Log::Init();

	Typhoon::Application *app = new Typhoon::Application;

	app->Run();

	delete app;

	return 0;

}