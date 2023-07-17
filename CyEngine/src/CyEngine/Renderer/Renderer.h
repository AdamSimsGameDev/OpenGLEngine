#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Cy
{
	class Mesh;

	class Renderer
	{
	public:
		static void BeginScene(Scene* scene);
		static void EndScene();

		static void Submit(Mesh* mesh);
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
