#include "cypch.h"
#include "WindowsInput.h"

#include "CyEngine/Application.h"
#include <GLFW/glfw3.h>
#include <CyEngine/KeyCode.h>

namespace Cy
{
	Input* Input::s_Instance = new WindowsInput();

	WindowsInput::WindowsInput()
	{
		// Setup "AllKeys" array
		AllKeys = 
		{
			CY_KEY_SPACE,
			CY_KEY_APOSTROPHE,
			CY_KEY_COMMA,
			CY_KEY_MINUS,
			CY_KEY_PERIOD,
			CY_KEY_SLASH,
			CY_KEY_0,
			CY_KEY_1,
			CY_KEY_2,
			CY_KEY_3,
			CY_KEY_4,
			CY_KEY_5,
			CY_KEY_6,
			CY_KEY_7,
			CY_KEY_8,
			CY_KEY_9,
			CY_KEY_SEMICOLON,
			CY_KEY_EQUAL,
			CY_KEY_A,
			CY_KEY_B,
			CY_KEY_C,
			CY_KEY_D,
			CY_KEY_E,
			CY_KEY_F,
			CY_KEY_G,
			CY_KEY_H,
			CY_KEY_I,
			CY_KEY_J,
			CY_KEY_K,
			CY_KEY_L,
			CY_KEY_M,
			CY_KEY_N,
			CY_KEY_O,
			CY_KEY_P,
			CY_KEY_Q,
			CY_KEY_R,
			CY_KEY_S,
			CY_KEY_T,
			CY_KEY_U,
			CY_KEY_V,
			CY_KEY_W,
			CY_KEY_X,
			CY_KEY_Y,
			CY_KEY_Z,
			CY_KEY_LEFT_BRACKET,
			CY_KEY_BACKSLASH,
			CY_KEY_RIGHT_BRACKET,
			CY_KEY_GRAVE_ACCENT,
			CY_KEY_WORLD_1,
			CY_KEY_WORLD_2,
			CY_KEY_ESCAPE,
			CY_KEY_ENTER,
			CY_KEY_TAB,
			CY_KEY_BACKSPACE,
			CY_KEY_INSERT,
			CY_KEY_DELETE,
			CY_KEY_RIGHT,
			CY_KEY_LEFT,
			CY_KEY_DOWN,
			CY_KEY_UP,
			CY_KEY_PAGE_UP,
			CY_KEY_PAGE_DOWN,
			CY_KEY_HOME,
			CY_KEY_END,
			CY_KEY_CAPS_LOCK,
			CY_KEY_SCROLL_LOCK,
			CY_KEY_NUM_LOCK,
			CY_KEY_PRINT_SCREEN,
			CY_KEY_PAUSE,
			CY_KEY_F1,
			CY_KEY_F2,
			CY_KEY_F3,
			CY_KEY_F4,
			CY_KEY_F5,
			CY_KEY_F6,
			CY_KEY_F7,
			CY_KEY_F8,
			CY_KEY_F9,
			CY_KEY_F10,
			CY_KEY_F11,
			CY_KEY_F12,
			CY_KEY_F13,
			CY_KEY_F14,
			CY_KEY_F15,
			CY_KEY_F16,
			CY_KEY_F17,
			CY_KEY_F18,
			CY_KEY_F19,
			CY_KEY_F20,
			CY_KEY_F21,
			CY_KEY_F22,
			CY_KEY_F23,
			CY_KEY_F24,
			CY_KEY_F25,
			CY_KEY_KP_0,
			CY_KEY_KP_1,
			CY_KEY_KP_2,
			CY_KEY_KP_3,
			CY_KEY_KP_4,
			CY_KEY_KP_5,
			CY_KEY_KP_6,
			CY_KEY_KP_7,
			CY_KEY_KP_8,
			CY_KEY_KP_9,
			CY_KEY_KP_DECIMAL,
			CY_KEY_KP_DIVIDE,
			CY_KEY_KP_MULTIPLY,
			CY_KEY_KP_SUBTRACT,
			CY_KEY_KP_ADD,
			CY_KEY_KP_ENTER,
			CY_KEY_KP_EQUAL,
			CY_KEY_LEFT_SHIFT,
			CY_KEY_LEFT_CONTROL,
			CY_KEY_LEFT_ALT,
			CY_KEY_LEFT_SUPER,
			CY_KEY_RIGHT_SHIFT,
			CY_KEY_RIGHT_CONTROL,
			CY_KEY_RIGHT_ALT,
			CY_KEY_RIGHT_SUPER,
			CY_KEY_MENU,
		};

		AllMouseButtons =
		{
			 CY_MOUSE_BUTTON_1,
			 CY_MOUSE_BUTTON_2,
			 CY_MOUSE_BUTTON_3,
			 CY_MOUSE_BUTTON_4,
			 CY_MOUSE_BUTTON_5,
			 CY_MOUSE_BUTTON_6,
			 CY_MOUSE_BUTTON_7,
			 CY_MOUSE_BUTTON_8,
		};
	}

	void WindowsInput::UpdateImpl()
	{
		auto window = Application::Get().GetWindow().GetNativeWindowTyped<GLFWwindow>();

		// set last frame keys from current cache
		LastPressedKeys = PressedKeys;
		LastPressedMouseButtons = PressedMouseButtons;

		// cache all of the keys into a keystate map
		for (int keycode : AllKeys)
		{
			PressedKeys[keycode] = glfwGetKey(window, keycode);
		}
		for (int button : AllMouseButtons)
		{
			PressedMouseButtons[button] = glfwGetMouseButton(window, button);
		}
	}

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		return PressedKeys[keycode] && !LastPressedKeys[keycode];
	}

	bool WindowsInput::IsKeyDownImpl(int keycode)
	{
		return PressedKeys[keycode];
	}

	bool WindowsInput::IsKeyReleasedImpl(int keycode)
	{
		return !PressedKeys[keycode] && LastPressedKeys[keycode];
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		return PressedMouseButtons[button] && !LastPressedMouseButtons[button];
	}

	bool WindowsInput::IsMouseButtonDownImpl(int button)
	{
		return PressedMouseButtons[button];
	}

	bool WindowsInput::IsMouseButtonReleasedImpl(int button)
	{
		return !PressedMouseButtons[button] && LastPressedMouseButtons[button];
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePosImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = Application::Get().GetWindow().GetNativeWindowTyped<GLFWwindow>();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
}
