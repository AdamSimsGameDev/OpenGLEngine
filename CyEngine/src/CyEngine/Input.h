#pragma once

#include "Core.h"

namespace Cy
{
	class CY_API Input
	{
	public:
		static void Update() { s_Instance->UpdateImpl(); }

		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsKeyDown(int keycode) { return s_Instance->IsKeyDownImpl(keycode); }
		static bool IsKeyReleased(int keycode) { return s_Instance->IsKeyReleasedImpl(keycode); }

		static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static bool IsMouseButtonDown(int button) { return s_Instance->IsMouseButtonDownImpl(button); }
		static bool IsMouseButtonReleased(int button) { return s_Instance->IsMouseButtonReleasedImpl(button); }

		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		static Vector2 GetMousePos() { return s_Instance->GetMousePosImpl(); }

		static Vector2 GetMouseDelta() { return s_Instance->GetMouseDeltaImpl(); }
		static Vector2 GetMouseDeltaNormalized() { return s_Instance->GetMouseDeltaNormalizedImpl(); }

	protected:
		virtual void UpdateImpl() { }

		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsKeyDownImpl(int keycode) = 0;
		virtual bool IsKeyReleasedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual bool IsMouseButtonDownImpl(int button) = 0;
		virtual bool IsMouseButtonReleasedImpl(int button) = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual Vector2 GetMousePosImpl() = 0;

		virtual Vector2 GetMouseDeltaImpl() = 0;
		virtual Vector2 GetMouseDeltaNormalizedImpl() = 0;

	private:
		static Input* s_Instance;
	};
}