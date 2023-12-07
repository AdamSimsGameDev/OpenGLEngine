#pragma once
#include "CameraComponent.h"
#include <glm/glm.hpp>
#include "generated/EditorCameraComponent.gen.h"

namespace Cy
{
	CLASS()
	class EditorCameraComponent : public CameraComponent
	{
		GENERATED_CLASS(EditorCameraComponent)

	public:
		virtual void Tick(float deltaTime) override;

	protected:
		PROPERTY()
		float MovementSpeed = 4.0f;

		PROPERTY()
		float TurnSpeed = 10.0f;

		PROPERTY()
		float XAngle = 0.0f;

		PROPERTY()
		float YAngle = 0.0f;
	};
}

