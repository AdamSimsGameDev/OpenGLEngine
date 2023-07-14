#include "cypch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Cy
{
	void Camera::SetPosition(const Vector3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(const glm::quat& rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 rotate = glm::mat4_cast(m_Rotation);
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), (glm::vec3)m_Position) * rotate;
		m_ViewMatrix = glm::inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
