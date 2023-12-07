#include "cypch.h"
#include "EditorCameraComponent.h"
#include "CyEngine/Objects/SceneObject.h"

namespace Cy
{
	void EditorCameraComponent::Tick(float deltaTime)
	{
		CameraComponent::Tick(deltaTime);

		Transform* transform = GetOwner()->GetTransform();
		if (Input::IsKeyDown(CY_KEY_W))
		{
			transform->AddPosition(transform->GetForwardVector() * deltaTime * MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_S))
		{
			transform->AddPosition(transform->GetForwardVector() * deltaTime * -MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_D))
		{
			transform->AddPosition(transform->GetRightVector() * deltaTime * MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_A))
		{
			transform->AddPosition(transform->GetRightVector() * deltaTime * -MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_SPACE))
		{
			transform->AddPosition(transform->GetUpVector() * deltaTime * MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_LEFT_CONTROL))
		{
			transform->AddPosition(transform->GetUpVector() * deltaTime * -MovementSpeed);
		}

		if (Input::IsMouseButtonDown(CY_MOUSE_BUTTON_RIGHT))
		{
			XAngle += deltaTime * TurnSpeed * -Input::GetMouseDelta().x;
			YAngle += deltaTime * TurnSpeed * -Input::GetMouseDelta().y;
			Quat pitch = Quat::FromEuler({ YAngle, 0.0f, 0.0f });
			Quat yaw = Quat::FromEuler({ 0.f, XAngle, 0.f });
			transform->SetRotation(pitch * yaw);
		}
	}
}
