#include "cypch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Cy
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: Camera(), m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
