#include "cypch.h"
#include "CubeObject.h"
#include "CyEngine/Renderer/Mesh.h"
#include "CyEngine/Renderer/Shader.h"

namespace Cy
{
	CubeObject::CubeObject()
	{
		CY_CORE_LOG("Creating MeshComponent");
		m_MeshComponent = CreateAndAddComponent<MeshComponent>();
		
		TestArr.Add(10);
		TestArr.Add(46);
		TestArr.Add(-12);
		TestArr.Add(0);

		std::vector<float> vertices = 
		{
			// TOP
			-0.5f,	 0.5f,	 0.5f,
			-0.5f,	 0.5f,	-0.5f,
			 0.5f,	 0.5f,	-0.5f,
			 0.5f,	 0.5f,	 0.5f,

			// BOTTOM
			 0.5f,	-0.5f,	 0.5f,
			 0.5f,	-0.5f,	-0.5f,
			-0.5f,	-0.5f,	-0.5f,
			-0.5f,	-0.5f,	 0.5f,

			// LEFT
			-0.5f,	 0.5f,	 0.5f,
			-0.5f,	-0.5f,	 0.5f,
			-0.5f,	-0.5f,	-0.5f,
			-0.5f,	 0.5f,	-0.5f,

			// RIGHT
			 0.5f,	 0.5f,	-0.5f,
			 0.5f,	-0.5f,	-0.5f,
			 0.5f,	-0.5f,	 0.5f,
			 0.5f,	 0.5f,	 0.5f,

			// FRONT
			-0.5f,	 0.5f,	 0.5f,
			-0.5f,	-0.5f,	 0.5f,
			 0.5f,	-0.5f,	 0.5f,
			 0.5f,	 0.5f,	 0.5f,

			// BACK
			 0.5f,	 0.5f,	-0.5f,
			 0.5f,	-0.5f,	-0.5f,
			-0.5f,	-0.5f,	-0.5f,
			-0.5f,	 0.5f,	-0.5f,
		};

		std::vector<float> normals =
		{
			// Top
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			// Bottom
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,

			// Left
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,

			// Right
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			// Front
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			// Back
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
		};

		std::vector<uint32_t> indices =
		{
			//Top
			0, 2, 1,
			0, 3, 2,
			
			//Bottom
			4, 6, 5,
			4, 7, 6,

			//Left
			8, 10, 9,
			8, 11, 10,

			//Right
			12, 14, 13,
			12, 15, 14,

			//Front
			17, 18, 16,
			18, 19, 16,

			//Back
			21, 22, 20,
			22, 23, 20
		};

		// Generate the mesh
		Mesh* mesh = new Mesh("Cube Mesh");
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
