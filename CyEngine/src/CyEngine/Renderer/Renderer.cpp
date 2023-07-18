#include "cypch.h"
#include "Renderer.h"

#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Renderer/Mesh.h"
#include "CyEngine/Renderer/Shader.h"
#include <CyEngine/Objects/CameraObject.h>

namespace Cy
{
	void Renderer::BeginScene(Scene* scene, Shader* shader)
	{
		RenderCommand::SetClearColour({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();

		shader->Bind();

		// get the first camera.
		std::vector<CameraObject*> cameras = scene->GetAllObjectsOfType<CameraObject>();
		if (cameras.size() == 0)
		{
			CY_CORE_ERROR("Unable to render as no cameras exist in scene! ");
			return;
		}

		// set shader view matrix
		Matrix4x4 matrix = cameras[0]->GetProjectionViewMatrix();
		shader->UploadUniformMat4("u_ViewProjection", matrix);

		for (Component* comp : scene->GetAllComponentsOfType("MeshComponent"))
		{
			if (MeshComponent* meshComp = CastChecked<MeshComponent>(comp))
			{
				Submit(meshComp->GetMesh());
			}
		}
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(Mesh* mesh)
	{
		Submit(mesh->m_VertexArray);
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
