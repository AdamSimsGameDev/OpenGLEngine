#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Cy
{
	class MeshComponent;
	class Shader;

	class Renderer
	{
	public:
		static void BeginScene(Scene* scene);
		static void EndScene();

		static void Submit(MeshComponent* comp);
		static void Submit(Shader* shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& objectMatrix);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			SceneData() : ViewProjectionMatrix(Matrix4x4(1.0f)) {}
			Matrix4x4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}
