#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#include "Command.h"
#include "UpCommand.h"
#include "DownCommand.h"
#include "RightCommand.h"
#include "LeftCommand.h"
#include "PumpCommand.h"

bool dae::InputManager::ProcessInput()
{
	// todo: read the input
	UpdateControllerStates();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}
	return true;
}

void dae::InputManager::InitializeControllers()
{
	if (m_IsInitialized)
		return;

	DWORD result;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE inputState;
		ZeroMemory(&inputState, sizeof(XINPUT_STATE));
		result = XInputGetState(i, &inputState);
		m_Controllers[i] = (result == ERROR_SUCCESS);
	}

	InitializeCommands();

	m_IsInitialized = true;
}

Command* dae::InputManager::IsPressed(ControllerButton button) const
{
	// todo: return whether the given button is pressed or not.
	if (m_PreviousControllerStates[0].Gamepad.wButtons & Controller_Buttons[(int)button])
	{
		Command* command = CheckButtonId(button);
		if (command != nullptr)
			return command;
	}

	return false;
}

Command * dae::InputManager::HandleInput() const
{
	Command* command = nullptr;

	if (GetKeyState('W') & 0x8000)
	{
		command = CheckButtonId(dae::ControllerButton::ButtonY);
		if (command != nullptr) return command;
	}

	if (GetKeyState('A') & 0x8000)
	{
		command = CheckButtonId(dae::ControllerButton::ButtonX);
		if (command != nullptr) return command;
	}
	if (GetKeyState('S') & 0x8000)
	{
		command = CheckButtonId(dae::ControllerButton::ButtonA);
		if (command != nullptr) return command;
	}
	if (GetKeyState('D') & 0x8000)
	{
		command = CheckButtonId(dae::ControllerButton::ButtonB);
		if (command != nullptr) return command;
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		command = CheckButtonId(dae::ControllerButton::RightShoulder);
		if (command != nullptr) return command;
	}


	command = IsPressed(dae::ControllerButton::ButtonA);
	if (command != nullptr) return command;

	command = IsPressed(dae::ControllerButton::ButtonB);
	if (command != nullptr) return command;

	command = IsPressed(dae::ControllerButton::ButtonX);
	if (command != nullptr) return command;

	command = IsPressed(dae::ControllerButton::ButtonY);
	if (command != nullptr) return command;

	command = IsPressed(dae::ControllerButton::RightShoulder);
	if (command != nullptr) return command;

	auto& input = InputManager::GetInstance();

	if (input.LeftStickUsingX())
	{
		if (m_CurrentControllerStates[0].Gamepad.sThumbLX > 0)
		{
			command = CheckButtonId(dae::ControllerButton::ButtonB);
			if (command != nullptr) return command;
		}
		else
		{
			command = CheckButtonId(dae::ControllerButton::ButtonX);
			if (command != nullptr) return command;
		}
	}

	if (input.LeftStickUsingY())
	{
		if (m_CurrentControllerStates[0].Gamepad.sThumbLY > 0)
		{
			command = CheckButtonId(dae::ControllerButton::ButtonY);
			if (command != nullptr) return command;
		}
		else
		{
			command = CheckButtonId(dae::ControllerButton::ButtonA);
			if (command != nullptr) return command;
		}
	}


	return nullptr;
}

Command* dae::InputManager::CheckButtonId(ControllerButton button) const
{
	if ((int)button == m_ButtonA->ButtonID) return m_ButtonA;
	if ((int)button == m_ButtonB->ButtonID) return m_ButtonB;
	if ((int)button == m_ButtonX->ButtonID) return m_ButtonX;
	if ((int)button == m_ButtonY->ButtonID) return m_ButtonY;
	if ((int)button == m_PumpCommand->ButtonID) return m_PumpCommand;

	return nullptr;
}

void dae::InputManager::InitializeCommands()
{
	m_ButtonA = new DownCommand();
	m_ButtonB = new RightCommand();
	m_ButtonX = new LeftCommand();
	m_ButtonY = new UpCommand();
	m_PumpCommand = new PumpCommand();
	
	m_ButtonA->ButtonID = 0;
	m_ButtonB->ButtonID = 1;
	m_ButtonX->ButtonID = 2;
	m_ButtonY->ButtonID = 3;
	m_PumpCommand->ButtonID = 9;
}

void dae::InputManager::UpdateControllerConfiguration(ControllerButton button, int id)
{
	CheckButtonId(button)->ButtonID = id;
}

bool dae::InputManager::LeftStickUsingX()
{
	auto x = m_CurrentControllerStates[0].Gamepad.sThumbLX;
	float normalizedX = fmaxf(-1, (float)x / 32767);

	if (abs(normalizedX) < 0.5f) return false;

	return true;
}

bool dae::InputManager::LeftStickUsingY()
{
	auto y = m_CurrentControllerStates[0].Gamepad.sThumbLY;
	float normalizedY = fmaxf(-1, (float)y / 32767);

	if (abs(normalizedY) < 0.5f) return false;

	return true;
}

void dae::InputManager::UpdateControllerStates()
{
	DWORD result;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		//Dont run if controller is not connected;
		if (!m_Controllers[i])
			return;

		m_PreviousControllerStates[i] = m_CurrentControllerStates[i];
		result = XInputGetState(i, &m_CurrentControllerStates[i]);
		m_Controllers[i] = (result == ERROR_SUCCESS);
	}
}

void dae::InputManager::Destroy()
{
	if (m_ButtonA != nullptr)
		delete m_ButtonA;

	if (m_ButtonB != nullptr)
		delete m_ButtonB;

	if (m_ButtonX != nullptr)
		delete m_ButtonX;

	if (m_ButtonY != nullptr)
		delete m_ButtonY;

	if (m_PumpCommand != nullptr)
		delete m_PumpCommand;
}