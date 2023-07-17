#include "cypch.h"
#include "Mesh.h"
#include "CyEngine/Renderer/VertexArray.h"
#include "CyEngine/Renderer/Buffer.h"

namespace Cy
{
	void Mesh::SetVertices(const std::vector<Vector3>& vertices)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			m_Vertices.push_back(vertices[i].x);
			m_Vertices.push_back(vertices[i].y);
			m_Vertices.push_back(vertices[i].z);
		}
	}

	void Mesh::SetVertices(const std::vector<float>& vertices)
	{
		m_Vertices = vertices;
	}

	void Mesh::SetTriangles(const std::vector<uint32_t>& triangles)
	{
		m_Triangles = triangles;
	}

	void Mesh::Generate()
	{
		m_VertexArray.reset(VertexArray::Create());
		m_VertexBuffer.reset(VertexBuffer::Create(m_Vertices.data(), sizeof(float) * m_Vertices.size()));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" }
		};

		m_VertexBuffer->SetLayout(layout);

		m_IndexBuffer.reset(IndexBuffer::Create(m_Triangles.data(), m_Triangles.size()));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}
}
