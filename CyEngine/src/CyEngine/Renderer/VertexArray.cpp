#include "cypch.h"
#include "VertexArray.h"

#include "CyEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Cy
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		return nullptr;
	}
}