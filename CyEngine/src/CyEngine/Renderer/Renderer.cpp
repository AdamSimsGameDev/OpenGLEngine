#include "cypch.h"
#include "Renderer.h"

#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Renderer/Mesh.h"
#include "CyEngine/Renderer/Shader.h"
#include <CyEngine/Objects/CameraObject.h>

namespace Cy
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Scene* scene)
	{
		RenderCommand::SetClearColour({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();

		// get the first camera.
		std::vector<CameraObject*> cameras = scene->GetAllObjectsOfType<CameraObject>();
		if (cameras.size() == 0)
		{
			CY_CORE_ERROR("Unable to render as no cameras exist in scene! ");
			return;
		}

		// set shader view matrix
		s_SceneData->ViewProjectionMatrix = cameras[0]->GetProjectionViewMatrix();

		for (Component* comp : scene->GetAllComponentsOfType("MeshComponent"))
		{
			if (MeshComponent* meshComp = CastChecked<MeshComponent>(comp))
			{
				Submit(meshComp);
			}
		}
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(MeshComponent* comp)
	{
		Submit(comp->GetShader(), comp->GetMesh()->m_VertexArray);
	}

	void Renderer::Submit(Shader* shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
