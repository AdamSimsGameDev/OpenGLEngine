#pragma once
#include "CyEngine/Core.h"
#include "generated/Mesh.gen.h"

namespace Cy
{
	class VertexBuffer;
	class IndexBuffer;
	class VertexArray;

	CLASS()
	class Mesh
	{
		GENERATED_CLASS(Mesh)

		friend class Renderer;

	public:
		Mesh() { }
		Mesh(const String& name);
		Mesh(const String& name, 
			const Array<float>& vertices,
			const Array<uint32_t>& triangles,
			const Array<float>& normals,
			const Array<float>& uvs);

		void SetVertices(const Array<Vector3>& vertices);
		void SetVertices(const Array<float>& vertices);

		void SetNormals(const Array<float>& normals);

		void SetTriangles(const Array<uint32_t>& triangles);

		void SetUVs(const Array<Vector2>& uvs);
		void SetUVs(const Array<float>& uvs);

		String GetName() const { return m_Name; }

		void Generate();

	private:
		String m_Name;

		Array<float> m_Packed;
		Array<float> m_Vertices;
		Array<float> m_Normals;
		Array<uint32_t> m_Triangles;
		Array<float> m_UVs;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;
	};
}
