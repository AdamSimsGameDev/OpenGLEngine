#pragma once
#include "Core.h"

namespace Cy
{
	class CY_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();
	};

	// Should be defined by projects.
	Application* CreateApplication();
}
