#include "cypch.h"
#include "WindowsWindow.h"
#include <CyEngine/Log.h>
#include <CyEngine/Events/ApplicationEvent.h>
#include <CyEngine/Events/KeyEvent.h>
#include <CyEngine/Events/MouseEvent.h>
#include <CyEngine/Events/WindowEvent.h>
#include <Platform/OpenGL/OpenGLContext.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Cy
{
	static bool s_GLFWInitialised = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		CY_CORE_ERROR("GLFW ERROR {0}: {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetUseVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const
	{
		return m_Data.VSync;
	}

	float WindowsWindow::GetTime() const
	{
		return (float)glfwGetTime();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		CY_CORE_LOG("Creating window of size ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialised)
		{
			int success = glfwInit();
			CY_CORE_ASSERT(success, "Failed to init GLFW. ");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialised = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetUseVSync(true);
	
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
			{  
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent e(width, height);
				data.EventCallback(e);
			});
		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int x, int y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowMoveEvent e(x, y);
				data.EventCallback(e);
			});
		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				if (focused)
				{
					WindowFocusEvent e;
					data.EventCallback(e);
				}
				else
				{
					WindowFocusLostEvent e;
					data.EventCallback(e);
				}
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent e;
				data.EventCallback(e);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);			
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressEvent pressed(key);
						data.EventCallback(pressed);
						break; 
					}
					case GLFW_RELEASE:
					{
						KeyReleaseEvent released(key);
						data.EventCallback(released);
						break; 
					}
					case GLFW_REPEAT:
					{
						KeyRepeatEvent repeated(key);
						data.EventCallback(repeated);
						break;
					}
				}
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyCharEvent e(codepoint);
				data.EventCallback(e);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						MousePressedEvent pressed(button);
						data.EventCallback(pressed);
						break; 
					}
					case GLFW_RELEASE:
					{
						MouseReleasedEvent released(button);
						data.EventCallback(released);
						break; 
					}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrollEvent e((float)xOffset, (float)yOffset);
				data.EventCallback(e);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMoveEvent e((float)x, (float)y);
				data.EventCallback(e);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}
