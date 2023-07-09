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
		static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

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
		virtual std::pair<float, float> GetMousePosImpl() = 0;

	private:
		static Input* s_Instance;
	};
}