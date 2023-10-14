#pragma once

namespace Cy
{
	class VertexBuffer;
	class IndexBuffer;
	class VertexArray;

	struct Vector3;

	class Mesh
	{
		friend class Renderer;

	public:
		Mesh(const std::string& name);

		void SetVertices(const std::vector<Vector3>& vertices);
		void SetVertices(const std::vector<float>& vertices);

		void SetNormals(const std::vector<float>& normals);

		void SetTriangles(const std::vector<uint32_t>& triangles);

		std::string GetName() const { return m_Name; }

		void Generate();

	private:
		std::string m_Name;

		std::vector<float> m_Packed;
		std::vector<float> m_Vertices;
		std::vector<float> m_Normals;
		std::vector<uint32_t> m_Triangles;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;
	};
}