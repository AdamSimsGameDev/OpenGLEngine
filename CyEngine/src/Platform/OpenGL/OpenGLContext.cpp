#include "cypch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cy
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
	{
		m_WindowHandle = window;
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CY_CORE_ASSERT(status, "Failed to initialise glad!");
		glEnable(GL_CULL_FACE);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
