#pragma once

#include <glm/glm.hpp>

namespace Cy
{
	class Camera
	{
	public:
		Camera() : m_ProjectionMatrix(1.0f), m_ViewMatrix(1.0f), m_ProjectionViewMatrix(1.0f)
		{
		}
		virtual ~Camera() { }

		const Transform& GetTransform() const { return m_Transform; }
		Transform& GetTransform() { return m_Transform; }

		virtual void SetPosition(const Vector3& position);
		virtual void SetRotation(const Quat& rotation);

		Vector3 GetPosition() const { return m_Transform.GetPosition(); }
		Quat GetRotation() const { return m_Transform.GetRotation(); }

		Matrix4x4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		Matrix4x4 GetViewMatrix() const { return m_ViewMatrix; }
		Matrix4x4 GetProjectionViewMatrix() const { return m_ProjectionViewMatrix;  }

	protected:
		void RecalculateViewMatrix();

	protected:
		Transform m_Transform;
		Matrix4x4 m_ProjectionMatrix, m_ViewMatrix, m_ProjectionViewMatrix;
	};
}

