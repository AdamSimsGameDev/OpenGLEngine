#include "cypch.h"
#include "PerspectiveCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Cy
{
	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane)
		: Camera(), m_FOV(fov), m_Width(width), m_Height(height), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		m_ProjectionMatrix = glm::perspectiveFov(m_FOV, m_Width, m_Height, m_NearPlane, m_FarPlane);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
