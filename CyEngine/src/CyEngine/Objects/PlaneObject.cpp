#include "cypch.h"
#include "PlaneObject.h"
#include "CyEngine/Renderer/Mesh.h"
#include "CyEngine/Renderer/Shader.h"

namespace Cy
{
	PlaneObject::PlaneObject()
	{
		CY_CORE_LOG("Creating MeshComponent");
		m_MeshComponent = CreateAndAddComponent<MeshComponent>();

		std::vector<float> vertices =
		{
			// TOP
			-0.5f,	 0.0f,	 0.5f,
			-0.5f,	 0.0f,	-0.5f,
			 0.5f,	 0.0f,	-0.5f,
			 0.5f,	 0.0f,	 0.5f,
		};

		std::vector<float> normals =
		{
			// Top
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
		};

		std::vector<uint32_t> indices =
		{
			//Top
			0, 2, 1,
			0, 3, 2,
		};

		// Generate the mesh
		Mesh* mesh = new Mesh("Plane Mesh");
		mesh->SetVertices(vertices);
		mesh->SetTriangles(indices);
		mesh->SetNormals(normals);
		mesh->Generate();

		// set the mesh.
		m_MeshComponent->SetMesh(mesh);

		// generate basic shader
		m_MeshComponent->SetShader(Shader::CreateFromFiles("resources/Shader.vert", "resources/Shader.frag"));
	}
}
