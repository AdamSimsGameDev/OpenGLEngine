#include "cypch.h"
#include "EditorCameraComponent.h"
#include "CyEngine/Objects/SceneObject.h"

namespace Cy
{
	void EditorCameraComponent::Tick(float deltaTime)
	{
		CameraComponent::Tick(deltaTime);

		Transform* transform = GetOwner()->GetTransform();
		Transform* parent = transform->GetParent();
		if (Input::IsKeyDown(CY_KEY_W))
		{
			parent->AddPosition(transform->GetForwardVector() * deltaTime * MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_S))
		{
			parent->AddPosition(transform->GetForwardVector() * deltaTime * -MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_D))
		{
			parent->AddPosition(transform->GetRightVector() * deltaTime * MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_A))
		{
			parent->AddPosition(transform->GetRightVector() * deltaTime * -MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_SPACE))
		{
			parent->AddPosition(Vector3::Up * deltaTime * MovementSpeed);
		}
		if (Input::IsKeyDown(CY_KEY_LEFT_CONTROL))
		{
			parent->AddPosition(Vector3::Up * deltaTime * -MovementSpeed);
		}

		if (Input::IsMouseButtonDown(CY_MOUSE_BUTTON_RIGHT))
		{
			XAngle += deltaTime * TurnSpeed * Input::GetMouseDelta().x;
			YAngle += deltaTime * TurnSpeed * -Input::GetMouseDelta().y;
			Quat pitch = Quat::FromEuler({ YAngle, 0.0f, 0.0f });
			Quat yaw = Quat::FromEuler({ 0.f, XAngle, 0.f });
			transform->SetRotation(pitch);
			parent->SetRotation(yaw);
		}
	}
}
