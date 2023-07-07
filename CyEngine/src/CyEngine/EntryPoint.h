#pragma once

#ifdef CY_PLATFORM_WINDOWS

extern Cy::Application* Cy::CreateApplication();

int main(int arcg, char** argv)
{
	Cy::Log::Init();
	CY_CORE_WARN("Initialized Log!");
	CY_INFO("Hello World! Var={0}", 5);

	Cy::Application* app = Cy::CreateApplication();
	app->Run();
	delete app;
}

#endif