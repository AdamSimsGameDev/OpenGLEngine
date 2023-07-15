#include "cypch.h"
#include "Camera.h"

namespace Cy
{
	void Camera::SetPosition(const Vector3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(const Quat& rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		Matrix4x4 rotate = Matrix4x4::MatCast(m_Rotation);
		Matrix4x4 transform = Matrix4x4::Translate(Matrix4x4(1.0f), m_Position) * rotate;
		m_ViewMatrix = Matrix4x4::Inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
