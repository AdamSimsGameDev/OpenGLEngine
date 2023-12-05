#include "cypch.h"
#include "Renderer.h"
#include "CyEngine/Components/CameraComponent.h"
#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Renderer/Mesh.h"
#include "CyEngine/Renderer/Shader.h"
#include "CyEngine/World.h"

namespace Cy
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(World* scene)
	{
		RenderCommand::SetClearColour({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();

		// get the first camera.
		Array<CameraComponent*> cameras = scene->GetAllComponentsOfType<CameraComponent>();
		if (cameras.Count() == 0)
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
				if (!meshComp->bIsVisible)
					continue;
				Submit(meshComp);
			}
		}
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(MeshComponent* comp)
	{
		Submit(comp->GetShader(), comp->GetMesh()->m_VertexArray, comp->GetParent<SceneObject>()->GetTransform().GetWorldTransformationMatrix());
	}

	void Renderer::Submit(Shader* shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& objectMatrix)
	{
		shader->Bind();
		shader->UploadUniformVec3("u_LightPosition", glm::vec3(1.5f, 1.5f, 1.5f));
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Model", objectMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
