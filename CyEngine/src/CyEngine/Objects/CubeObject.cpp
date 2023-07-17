#include "cypch.h"
#include "CubeObject.h"
#include "CyEngine/Renderer/Mesh.h"

namespace Cy
{
	CubeObject::CubeObject()
	{
		CY_CORE_LOG("Creating MeshComponent");
		m_MeshComponent = CreateAndAddComponent<MeshComponent>();
		
		std::vector<float> vertices = 
		{
			-0.5f,	-0.5f,	 0.5f,
			 0.5f,	-0.5f,	 0.5f,
			-0.5f,	 0.5f,	 0.5f,
			 0.5f,	 0.5f,	 0.5f,
			-0.5f,	-0.5f,	-0.5f,
			 0.5f,	-0.5f,	-0.5f,
			-0.5f,	 0.5f,	-0.5f,
			 0.5f,	 0.5f,	-0.5f,
		};

		std::vector<uint32_t> indices =
		{
			//Top
			2, 6, 7,
			2, 3, 7,

			//Bottom
			0, 4, 5,
			0, 1, 5,

			//Left
			0, 2, 6,
			0, 4, 6,

			//Right
			1, 3, 7,
			1, 5, 7,

			//Front
			0, 2, 3,
			0, 1, 3,

			//Back
			4, 6, 7,
			4, 5, 7
		};

		// Generate the mesh
		Mesh* mesh = new Mesh("Cube Mesh");
		mesh->SetVertices(vertices);
		mesh->SetTriangles(indices);
		mesh->Generate();
		
		// set the mesh.
		m_MeshComponent->SetMesh(mesh);
	}
}
