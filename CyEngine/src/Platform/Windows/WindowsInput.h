#pragma once

#include "CyEngine/Input.h"

namespace Cy
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();

	protected:
		virtual void UpdateImpl() override;

		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsKeyDownImpl(int keycode) override;
		virtual bool IsKeyReleasedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual bool IsMouseButtonDownImpl(int button) override;
		virtual bool IsMouseButtonReleasedImpl(int button) override;

		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual Vector2 GetMousePosImpl() override;

		virtual Vector2 GetMouseDeltaImpl() override { return MouseDelta; }
		virtual Vector2 GetMouseDeltaNormalizedImpl() override { return MouseDeltaNormalized; }

	private:
		std::vector<int> AllKeys;
		std::unordered_map<int, bool> PressedKeys;
		std::unordered_map<int, bool> LastPressedKeys;

		std::vector<int> AllMouseButtons;
		std::unordered_map<int, bool> PressedMouseButtons;
		std::unordered_map<int, bool> LastPressedMouseButtons;

		Vector2 MouseDelta;
		Vector2 MouseDeltaNormalized;
		Vector2 LastMousePosition;
	};
}

