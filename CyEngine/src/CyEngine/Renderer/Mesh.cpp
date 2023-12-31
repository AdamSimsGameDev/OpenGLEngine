#include "cypch.h"
#include "Mesh.h"
#include "CyEngine/Renderer/VertexArray.h"
#include "CyEngine/Renderer/Buffer.h"
#include "CyEngine/String.h"

namespace Cy
{
	Mesh::Mesh(const String& name)
	{
		m_Name = name;
	}

	Mesh::Mesh(const String& name, const std::vector<float>& vertices, const std::vector<uint32_t>& triangles, const std::vector<float>& normals)
	{
		m_Name = name;
		SetVertices(vertices);
		SetTriangles(triangles);
		SetNormals(normals);
	}

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
		std::reverse(m_Triangles.begin(), m_Triangles.end());
	}

	void Mesh::SetNormals(const std::vector<float>& normals)
	{
		m_Normals = normals;
	}

	void Mesh::Generate()
	{
		m_Packed.reserve(m_Vertices.size() + m_Normals.size());
		CY_ASSERT(m_Vertices.size() == m_Normals.size(), "Normals and Vertices arrays should be of the same length!");

		for (int i = 0; i < m_Vertices.size(); i+=3)
		{
			m_Packed.push_back(m_Vertices[i]);
			m_Packed.push_back(m_Vertices[i + 1]);
			m_Packed.push_back(m_Vertices[i + 2]);
			m_Packed.push_back(m_Normals[i]);
			m_Packed.push_back(m_Normals[i + 1]);
			m_Packed.push_back(m_Normals[i + 2]);
		}

		m_VertexArray.reset(VertexArray::Create());
		m_VertexBuffer.reset(VertexBuffer::Create(m_Packed.data(), (uint32_t)(sizeof(float) * m_Packed.size())));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal"},
		};

		m_VertexBuffer->SetLayout(layout);

		m_IndexBuffer.reset(IndexBuffer::Create(m_Triangles.data(), (uint32_t)m_Triangles.size()));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}
}
