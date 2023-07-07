#pragma once

#ifdef CY_PLATFORM_WINDOWS

extern Cy::Application* Cy::CreateApplication();

int main(int arcg, char** argv)
{
	Cy::Application* app = Cy::CreateApplication();
	app->Run();
	delete app;
}

#endif