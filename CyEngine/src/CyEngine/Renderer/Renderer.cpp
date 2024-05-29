#include "cypch.h"
#include "Renderer.h"
#include "CyEngine/Components/CameraComponent.h"
#include "CyEngine/Components/LightComponent.h"
#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Renderer/Mesh.h"
#include "CyEngine/Renderer/Shader.h"
#include "CyEngine/Textures/Texture.h"
#include "CyEngine/World.h"

namespace Cy
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(World* scene)
	{
		RenderCommand::SetClearColour({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();

		// get the first camera.
		CameraComponent* mainCamera = nullptr;
#if CY_EDITOR
		if (scene->bIsEditorWorld)
		{
			mainCamera = scene->EditorCamera->GetComponent<CameraComponent>();
		}
		else
		{
#endif
			Array<CameraComponent*> cameras = scene->GetAllComponentsOfType<CameraComponent>();
			if (cameras.Count() == 0)
			{
				CY_CORE_ERROR("Unable to render as no cameras exist in scene! ");
				return;
			}
			mainCamera = cameras[0];
#if CY_EDITOR
		}
#endif

		s_SceneData->ViewProjectionMatrix = mainCamera->GetProjectionViewMatrix();

		// gather the main light
		Array<LightComponent*> lights = scene->GetAllComponentsOfType<LightComponent>();
		if (lights.Count() > 0)
		{
			const Transform& transform = lights[0]->GetParent<SceneObject>()->GetTransform();
			s_SceneData->MainLightPosition = transform.GetPosition();
			s_SceneData->MainLightDirection = transform.GetForwardVector();
			s_SceneData->MainLightColour = lights[0]->LightColour;
		}
		else
		{
			s_SceneData->MainLightDirection = Vector3::Zero;
			s_SceneData->MainLightPosition = Vector3::Zero;
			s_SceneData->MainLightColour = Vector4::Zero;
		}

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
		if (!comp->GetMesh() || !comp->GetShader())
			return;
		comp->m_Texture->Bind();
		Submit(comp->GetShader(), comp->GetMesh()->m_VertexArray, comp->GetParent<SceneObject>()->GetTransform().GetWorldTransformationMatrix());
	}

	void Renderer::Submit(Shader* shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4x4& objectMatrix)
	{
		shader->Bind();
		shader->UploadUniformVec3("u_LightPosition", s_SceneData->MainLightPosition);
		shader->UploadUniformVec3("u_LightDirection", s_SceneData->MainLightDirection.Normalized());
		shader->UploadUniformVec4("u_LightColour", s_SceneData->MainLightColour);

		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Model", objectMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
