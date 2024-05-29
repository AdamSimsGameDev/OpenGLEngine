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

	Mesh::Mesh(const String& name, const Array<float>& vertices, const Array<uint32_t>& triangles, const Array<float>& normals, const Array<float>& uvs)
	{
		m_Name = name;
		SetVertices(vertices);
		SetTriangles(triangles);
		SetNormals(normals);
		SetUVs(uvs);
	}

	void Mesh::SetVertices(const Array<Vector3>& vertices)
	{
		for (int i = 0; i < vertices.Count(); i++)
		{
			m_Vertices.Add(vertices[i].x);
			m_Vertices.Add(vertices[i].y);
			m_Vertices.Add(vertices[i].z);
		}
	}

	void Mesh::SetVertices(const Array<float>& vertices)
	{
		m_Vertices = vertices;
	}

	void Mesh::SetTriangles(const Array<uint32_t>& triangles)
	{
		m_Triangles = triangles;
		m_Triangles.Reverse();
	}

	void Mesh::SetUVs(const Array<Vector2>& uvs)
	{
		for (int i = 0; i < uvs.Count(); i++)
		{
			m_Vertices.Add(uvs[i].x);
			m_Vertices.Add(uvs[i].y);
		}
	}

	void Mesh::SetUVs(const Array<float>& uvs)
	{
		m_UVs = uvs;
	}

	void Mesh::SetNormals(const Array<float>& normals)
	{
		m_Normals = normals;
	}

	void Mesh::Generate()
	{
		m_Packed.Reserve(m_Vertices.Count() + m_Normals.Count());
		CY_ASSERT(m_Vertices.Count() == m_Normals.Count(), "Normals and Vertices arrays should be of the same length!");

		// make sure the uvs array is big enough
		int uvCount = m_UVs.Count();
		for (int i = 0; i < (m_Vertices.Count() / 3) - (uvCount / 2) + 1; i++)
		{
			m_UVs.Add(0.0f);
			m_UVs.Add(0.0f);
		}

		int uv = 0;
		for (int i = 0; i < m_Vertices.Count(); i+=3, uv+=2)
		{
			m_Packed.Add(m_Vertices[i]);
			m_Packed.Add(m_Vertices[i + 1]);
			m_Packed.Add(m_Vertices[i + 2]);
			m_Packed.Add(m_Normals[i]);
			m_Packed.Add(m_Normals[i + 1]);
			m_Packed.Add(m_Normals[i + 2]);
			m_Packed.Add(m_UVs[uv]);
			m_Packed.Add(m_UVs[uv + 1]);
		}

		m_VertexArray.reset(VertexArray::Create());
		m_VertexBuffer.reset(VertexBuffer::Create(m_Packed.Data(), (uint32_t)(sizeof(float) * m_Packed.Count())));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Normal"},
			{ ShaderDataType::Float2, "a_TexCoord"},
		};

		m_VertexBuffer->SetLayout(layout);

		m_IndexBuffer.reset(IndexBuffer::Create(m_Triangles.Data(), (uint32_t)m_Triangles.Count()));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}
}
