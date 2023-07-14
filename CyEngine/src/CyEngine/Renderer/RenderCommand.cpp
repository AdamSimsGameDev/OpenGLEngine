#include "cypch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Cy
{
	RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI();
}
