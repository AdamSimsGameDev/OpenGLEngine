#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
		virtual void SetRotation(const glm::quat& rotation);

		const Vector3& GetPosition() const { return m_Position; }
		const glm::quat& GetRotation() const { return m_Rotation; }

		glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetProjectionViewMatrix() const { return m_ProjectionViewMatrix;  }

	protected:
		void RecalculateViewMatrix();

	protected:
		glm::mat4 m_ProjectionMatrix, m_ViewMatrix, m_ProjectionViewMatrix;

		Vector3 m_Position;
		glm::quat m_Rotation;
	};
}

