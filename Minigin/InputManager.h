#pragma once
#include <XInput.h>
#include "Singleton.h"

class Command;

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	static const WORD Controller_Buttons[] =
	{
		XINPUT_GAMEPAD_A,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_Y,
		XINPUT_GAMEPAD_DPAD_UP,
		XINPUT_GAMEPAD_DPAD_DOWN,
		XINPUT_GAMEPAD_DPAD_LEFT,
		XINPUT_GAMEPAD_DPAD_RIGHT,
		XINPUT_GAMEPAD_LEFT_SHOULDER,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,
		XINPUT_GAMEPAD_LEFT_THUMB,
		XINPUT_GAMEPAD_RIGHT_THUMB,
		XINPUT_GAMEPAD_START,
		XINPUT_GAMEPAD_BACK,
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void InitializeControllers();
		void InitializeCommands();

		void UpdateControllerConfiguration(ControllerButton button, int id);

		void Destroy();

	private:
		void UpdateControllerStates();
		Command* CheckButtonId(ControllerButton button) const;

		bool m_IsInitialized = false;
		bool m_Controllers[XUSER_MAX_COUNT];
		XINPUT_STATE m_CurrentControllerStates[XUSER_MAX_COUNT];
		XINPUT_STATE m_PreviousControllerStates[XUSER_MAX_COUNT];

		//Commands
		Command* m_ButtonA;
		Command* m_ButtonB;
		Command* m_ButtonX;
		Command* m_ButtonY;
	};
}
