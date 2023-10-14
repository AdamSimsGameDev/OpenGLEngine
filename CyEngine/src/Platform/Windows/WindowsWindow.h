#pragma once
#include "CyEngine/Window.h"
#include "CyEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Cy
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual unsigned int GetWidth() const override { return m_Data.Width; }
		virtual unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFunc& callback) override { m_Data.EventCallback = callback; }
		virtual void SetUseVSync(bool enabled) override;
		virtual bool IsVSyncEnabled() const override;

		virtual void* GetNativeWindow() const { return m_Window; }

		virtual float GetTime() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			String Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFunc EventCallback;
		};

		WindowData m_Data;
	};
}
