#include "cypch.h"
#include "CameraComponent.h"
#include "CyEngine/Objects/SceneObject.h"

namespace Cy
{
	void CameraComponent::Tick(float deltaTime)
	{
		Component::Tick(deltaTime);

		// TODO: Not do this on tick
		RecalculateViewMatrix();
	}

	void CameraComponent::InitPerspectiveCamera(const PerspectiveCameraSettings& settings)
	{
		m_FOV = settings.FOV;
		m_Width = settings.Width;
		m_Height = settings.Height;
		m_NearPlane = settings.NearPlane;
		m_FarPlane = settings.FarPlane;

		m_ProjectionMatrix = glm::perspectiveFov(m_FOV, m_Width, m_Height, m_NearPlane, m_FarPlane);
		m_ProjectionMatrix = glm::scale(m_ProjectionMatrix, { 1.0f, 1.0f, -1.0f });
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void CameraComponent::InitOrthographicCamera(const OrthographicCameraSettings& settings)
	{
		m_Left = settings.Left;
		m_Right = settings.Right;
		m_Top = settings.Top;
		m_Bottom = settings.Bottom;

		m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -1.0f, 1.0f);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void CameraComponent::RecalculateViewMatrix()
	{
		Matrix4x4 rotate = Matrix4x4::MatCast(GetOwner()->GetTransform().GetRotation());
		Matrix4x4 transform = Matrix4x4::Translate(Matrix4x4(1.0f), GetOwner()->GetTransform().GetPosition()) * rotate;
		m_ViewMatrix = Matrix4x4::Inverse(transform);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
