#pragma once
#include "Core.h"
#include "Events/Event.h"
#include <string>
#include <functional>

namespace Cy
{
	struct CY_API WindowProps
	{
		int Width;
		int Height;
		std::string Title;

		WindowProps()
			: Width(1280), Height(720), Title("CyEngine Application")
		{
		}
		WindowProps(int width, int height, std::string title)
			: Width(width), Height(height), Title(title)
		{
		}
	};

	class CY_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
	
		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void SetUseVSync(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}
