#pragma once

#include "Camera.h"

namespace Cy
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

	private:
		float m_Left, m_Right, m_Top, m_Bottom;
	};
}
