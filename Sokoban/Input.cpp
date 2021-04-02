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

	//	int nJoysticks = SDL_NumJoysticks();
	numGamepads = 0;
	//
	//	// Count how many controllers there are
	//	for (int i = 0; i < nJoysticks; i++)
	//	{
	//		if (SDL_IsGameController(i))
	//		{
	//			numGamepads++;
	//		}
	//	}
	//
	//	// If we have some controllers attached
	//	if (numGamepads > 0)
	//	{
	//		for (int i = 0; i < numGamepads; i++)
	//		{
	//			// Open the controller and add it to our list
	//			SDL_GameController* pad = SDL_GameControllerOpen(i);
	//
	//			if (SDL_GameControllerGetAttached(pad) == 1)
	//			{
	//				m_connectedControllers.push_back(pad);
	//				m_isControllerInitialised = true;
	//			}
	//#if _DEBUG
	//			else
	//			{
	//				std::cout << "SDL_GetError() = " << SDL_GetError() << std::endl;
	//			}
	//#endif // _DEBUG
	//		}

	SDL_GameControllerEventState(SDL_ENABLE);
	//}

	//// Vectors are empty to begin with, this sets their size
	//m_controllerInputs.resize(numGamepads);
	//m_lastControllerInputs.resize(numGamepads);

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
	if (numGamepads == 0)
	{
		//InitialiseController();
	}

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

	if (SDL_PollEvent(&m_event))
	{
		switch (m_event.type) {
			// This happens when a device is added
			// A future improvement is to cope with new controllers being plugged in
			// when the game is running
		case SDL_CONTROLLERDEVICEADDED:
			if (SDL_IsGameController(m_event.cdevice.which))
			{
				AddController(m_event.cdevice.which);
			}

			break;
		case SDL_CONTROLLERDEVICEREMOVED:
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

void Input::DestroyInput()
{
	for (int i = 0; i < m_connectedControllers.size(); i++)
	{
		SDL_GameControllerClose(m_connectedControllers[i]);
	}
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

bool Input::IsControllerInitialised()
{
	return m_isControllerInitialised;
}

void Input::AddController(int deviceID)
{
	SDL_GameController* pad = SDL_GameControllerOpen(deviceID);

	if (SDL_GameControllerGetAttached(pad) == 1)
	{
		m_connectedControllers.push_back(pad);
		m_isControllerInitialised = true;

		numGamepads++;

		m_controllerInputs.resize(numGamepads);
		m_lastControllerInputs.resize(numGamepads);
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

	if (numGamepads == 0)
	{
		m_isControllerInitialised = false;
	}

	m_controllerInputs.resize(numGamepads);
	m_lastControllerInputs.resize(numGamepads);
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
