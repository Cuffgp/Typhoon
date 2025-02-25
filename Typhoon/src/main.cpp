#include "typch.h"

#include "Typhoon/Core/Log.h"

#include "Typhoon/Core/Application.h"

int main ()
{
	Typhoon::Log::Init();
	Typhoon::DirectXDevice::Init();

	Typhoon::Application *app = new Typhoon::Application;

	app->Run();

	delete app;

	Typhoon::DirectXDevice::Destroy();

	return 0;

}