#include "cypch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Cy
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		GameTickEvent e;
		CY_TRACE(e.ToString());

		while (true)
		{
			// DO
		}
	}
}