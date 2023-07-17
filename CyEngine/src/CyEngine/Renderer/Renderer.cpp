#include "cypch.h"
#include "Renderer.h"

#include "CyEngine/Components/MeshComponent.h"
#include "CyEngine/Renderer/Mesh.h"

namespace Cy
{
	void Renderer::BeginScene(Scene* scene)
	{
		RenderCommand::SetClearColour({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();

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
