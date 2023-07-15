#pragma once

#include <glm/glm.hpp>

namespace Cy
{
	class Camera
	{
	public:
		Camera() : m_ProjectionMatrix(1.0f), m_ViewMatrix(1.0f), m_ProjectionViewMatrix(1.0f), m_Position(0.0f, 0.0f, 0.0f), m_Rotation(1.0f, 0.0f, 0.0f, 0.0f)
		{
		}
		virtual ~Camera() { }

		virtual void SetPosition(const Vector3& position);
		virtual void SetRotation(const Quat& rotation);

		const Vector3& GetPosition() const { return m_Position; }
		const Quat& GetRotation() const { return m_Rotation; }

		Matrix4x4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		Matrix4x4 GetViewMatrix() const { return m_ViewMatrix; }
		Matrix4x4 GetProjectionViewMatrix() const { return m_ProjectionViewMatrix;  }

	protected:
		void RecalculateViewMatrix();

	protected:
		Matrix4x4 m_ProjectionMatrix, m_ViewMatrix, m_ProjectionViewMatrix;

		Vector3 m_Position;
		Quat m_Rotation;
	};
}

