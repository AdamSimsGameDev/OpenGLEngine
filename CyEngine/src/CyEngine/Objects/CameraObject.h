#pragma once
#include "SceneObject.h"
#include <glm/glm.hpp>
#include "generated/CameraObject.gen.h"

namespace Cy
{
	struct PerspectiveCameraSettings
	{
		float FOV;
		float Width;
		float Height;
		float NearPlane;
		float FarPlane;
	};

	struct OrthographicCameraSettings
	{
		float Left;
		float Right;
		float Top;
		float Bottom;
	};

	CLASS()
	class CameraObject : public SceneObject
	{
		GENERATED_CLASS(CameraObject)

	public:
		CameraObject() : SceneObject(), m_ProjectionMatrix(1.0f), m_ViewMatrix(1.0f), m_ProjectionViewMatrix(1.0f)
		{
			Name = "Camera";
		}
		virtual ~CameraObject() { }

		virtual void Tick(float deltaTime) override;

		virtual void InitPerspectiveCamera(const PerspectiveCameraSettings& settings);
		virtual void InitOrthographicCamera(const OrthographicCameraSettings& settings);

		Matrix4x4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		Matrix4x4 GetViewMatrix() const { return m_ViewMatrix; }
		Matrix4x4 GetProjectionViewMatrix() const { return m_ProjectionViewMatrix;  }

		PROPERTY()
		float RotationSpeed = 10.0f;

	protected:
		void RecalculateViewMatrix();

	protected:
		Matrix4x4 m_ProjectionMatrix, m_ViewMatrix, m_ProjectionViewMatrix;

		// Orthographic
		float m_Left, m_Right, m_Top, m_Bottom;

		// Perspective
		float m_FOV, m_Width, m_Height, m_NearPlane, m_FarPlane;
	};
}

