#pragma once

#include "Camera.h"

namespace Cy
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float width, float height, float nearPlane, float farPlane);

	private:
		float m_FOV, m_Width, m_Height, m_NearPlane, m_FarPlane;
	};
}
