#pragma once

#include "CyEngine/Core.h"
#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Cy
{
	class MeshComponent;
	class Shader;
	class World;

	class Renderer
	{
	public:
		static void BeginScene(World* scene);
		static void EndScene();

		static void Submit(MeshComponent* comp);
		static void Submit(Shader* shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& objectMatrix);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			SceneData() 
				: ViewProjectionMatrix(Matrix4x4(1.0f))
				, MainLightPosition(Vector3::Zero)
				, MainLightDirection(Vector3::Zero)
				, MainLightColour(Vector4::One)
			{
			}

			Matrix4x4 ViewProjectionMatrix;

			Vector3 MainLightPosition;
			Vector3 MainLightDirection;
			Vector4 MainLightColour;
		};

		static SceneData* s_SceneData;
	};
}
