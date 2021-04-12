#include "Input.h"

Input::Input()
{
	InitialiseController();
}

Input::~Input()
{
	DestroyInput();
}

void Input::InitialiseController()
{
	if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
	}

	numGamepads = 0;

	SDL_GameControllerEventState(SDL_ENABLE);

	//// Set the status of the controllers to "nothing is happening"
	//for (int i = 0; i < numGamepads; i++)
	//{
	//	for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
	//	{
	//		m_controllerInputs[i].axis[a] = 0;
	//		m_lastControllerInputs[i].axis[a] = 0;
	//	}
	//	for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
	//	{
	//		m_controllerInputs[i].buttons[b] = false;
	//		m_lastControllerInputs[i].buttons[b] = false;
	//	}
	//}
}

void Input::Update()
{
	// Copies the the button and axis states from the previous frame into the lastControllerInputs vector
	for (int i = 0; i < numGamepads; i++)
	{
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
		{
			m_lastControllerInputs[i].axis[a] = m_controllerInputs[i].axis[a];
		}
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
		{
			m_lastControllerInputs[i].buttons[b] = m_controllerInputs[i].buttons[b];
		}
	}

	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type) {
		case SDL_CONTROLLERDEVICEADDED:
			// TODO: Maybe limit how many controllers the game register
			std::cout << "Device has been connected" << std::endl;

			if (SDL_IsGameController(m_event.cdevice.which))
			{
				AddController(m_event.cdevice.which);
			}

			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			std::cout << "Device has been removed" << std::endl;
			RemoveController(m_event.cdevice.which);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			// Cycle through the controllers
			for (int i = 0; i < numGamepads; i++)
			{
				// Looking for the button that was pressed
				if (m_event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_connectedControllers[i])))
				{
					m_controllerInputs[i].buttons[m_event.cbutton.button] = true;
				}
			}
			break;
		case SDL_CONTROLLERBUTTONUP:
			for (int i = 0; i < numGamepads; i++)
			{
				if (m_event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_connectedControllers[i])))
				{
					m_controllerInputs[i].buttons[m_event.cbutton.button] = false;
				}
			}
			break;
		case SDL_CONTROLLERAXISMOTION:
			for (int i = 0; i < numGamepads; i++)
			{
				if (m_event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(m_connectedControllers[i])))
				{
					m_controllerInputs[i].axis[m_event.caxis.axis] = ProcessAxisInput(m_event.jaxis.value);
				}
			}
			break;
		}
	}
}

void Input::ResizeInputVectors()
{
	m_controllerInputs.resize(numGamepads);
	m_lastControllerInputs.resize(numGamepads);
}

bool Input::IsControllerInitialised()
{
	return m_isControllerInitialised;
}

void Input::AddController(int deviceID)
{
	SDL_GameController* pad = SDL_GameControllerOpen(deviceID);

	std::cout << SDL_GameControllerName(pad) << std::endl;

	if (SDL_GameControllerGetAttached(pad) == 1)
	{
		m_connectedControllers.push_back(pad);
		m_isControllerInitialised = true;

		numGamepads++;

		ResizeInputVectors();
	}
}

void Input::RemoveController(int deviceID)
{
	SDL_Joystick* joystick = SDL_JoystickFromInstanceID(deviceID);

	for (size_t i = 0; i < m_connectedControllers.size(); i++)
	{
		SDL_Joystick* tempJoystick = SDL_GameControllerGetJoystick(m_connectedControllers[i]);

		if (tempJoystick == joystick)
		{
			SDL_GameControllerClose(m_connectedControllers[i]);

			m_connectedControllers.erase(m_connectedControllers.begin() + i);
		}
	}

	numGamepads--;

	ResizeInputVectors();

	if (numGamepads == 0)
	{
		m_isControllerInitialised = false;
	}

}

void Input::DestroyInput()
{
	for (int i = 0; i < m_connectedControllers.size(); i++)
	{
		SDL_GameControllerClose(m_connectedControllers[i]);
		numGamepads--;
	}

	ResizeInputVectors();
}

// Has a button been pressed
bool Input::IsControllerButtonPressed(Controllers controllerID, SDL_GameControllerButton button)
{
	if (controllerID < 0 || controllerID > numGamepads) return false;

	return m_controllerInputs[controllerID].buttons[button] && !m_lastControllerInputs[controllerID].buttons[button];
}

// Is a button being pressed
bool Input::IsControllerButtonHeld(Controllers controllerID, SDL_GameControllerButton button)
{
	if (controllerID < 0 || controllerID > numGamepads) return false;

	return m_controllerInputs[controllerID].buttons[button] && m_lastControllerInputs[controllerID].buttons[button];
}

float Input::GetControllerAxis(Controllers controllerID, SDL_GameControllerAxis axis)
{
	if (controllerID < 0 || controllerID > numGamepads) return 0.0;

	return m_controllerInputs[controllerID].axis[axis];
}

int Input::ProcessAxisInput(float input)
{
	// Right or Down
	if (input > DEADZONE)
	{
		return 1;
	}
	// Left or Up
	else if (input < -DEADZONE)
	{
		return -1;
	}

	return 0;
}


