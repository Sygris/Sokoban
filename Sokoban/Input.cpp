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

	if (SDL_NumJoysticks > 0)
	{
		SDL_GameController* gamepad = nullptr;

		if (SDL_IsGameController)
		{
			gamepad = SDL_GameControllerOpen(0);

			if (gamepad)
			{
				m_controller = gamepad;
			}
#if _DEBUG
			else
			{
				fprintf(stderr, "Could not open controller: %s\n", SDL_GetError());
			}
#endif // _DEBUG

			SDL_GameControllerEventState(SDL_ENABLE);
			m_isControllerInitialised = true;

			std::cout << "Initialised 1 Gamepad" << std::endl;
		}
	}
	else
	{
		m_isControllerInitialised = false;
	}
}

void Input::Update()
{
	if (!m_isControllerInitialised)
	{
		InitialiseController();
	}

	while (SDL_PollEvent(&m_event) != NULL)
	{
		if (m_event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			SDL_ControllerButtonEvent buttonPressed = m_event.cbutton;

			switch (buttonPressed.button)
			{
			case SDL_CONTROLLER_BUTTON_DPAD_UP:
				m_buttonsPressed[UP] = true;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
				m_buttonsPressed[DOWN] = true;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
				m_buttonsPressed[LEFT] = true;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
				m_buttonsPressed[RIGHT] = true;
				break;
			case SDL_CONTROLLER_BUTTON_A:
				m_buttonsPressed[A] = true;
				break;
			case SDL_CONTROLLER_BUTTON_X:
				m_buttonsPressed[X] = true;
				break;
			case SDL_CONTROLLER_BUTTON_Y:
				m_buttonsPressed[Y] = true;
				break;
			case SDL_CONTROLLER_BUTTON_B:
				m_buttonsPressed[B] = true;
				break;
			case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
				m_buttonsPressed[L1] = true;
				break;
			case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
				m_buttonsPressed[R1] = true;
				break;
			default:
				break;
			}
		}
		else if (m_event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			SDL_ControllerButtonEvent buttonPressed = m_event.cbutton;

			switch (buttonPressed.button)
			{
			case SDL_CONTROLLER_BUTTON_DPAD_UP:
				m_buttonsPressed[UP] = false;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
				m_buttonsPressed[DOWN] = false;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
				m_buttonsPressed[LEFT] = false;
				break;
			case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
				m_buttonsPressed[RIGHT] = false;
				break;
			case SDL_CONTROLLER_BUTTON_A:
				m_buttonsPressed[A] = false;
				break;
			case SDL_CONTROLLER_BUTTON_X:
				m_buttonsPressed[X] = false;
				break;
			case SDL_CONTROLLER_BUTTON_Y:
				m_buttonsPressed[Y] = false;
				break;
			case SDL_CONTROLLER_BUTTON_B:
				m_buttonsPressed[B] = false;
				break;
			case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
				m_buttonsPressed[L1] = false;
				break;
			case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
				m_buttonsPressed[R1] = false;
				break;
			default:
				break;
			}
		}
		else if (m_event.type == SDL_CONTROLLERDEVICEREMOVED)
		{
			std::cout << "Gamepad Removed" << std::endl;
		}
		else if (m_event.type == SDL_CONTROLLERAXISMOTION)
		{
			if (m_event.caxis.value > 8000)
			{
				std::cout << "RIGHT" << std::endl;
			}
			else if (m_event.caxis.value < -8000)
			{
				std::cout << "LEFT" << std::endl;
			}
		}
	}
}

void Input::DestroyInput()
{
	if (m_isControllerInitialised)
	{
		SDL_GameControllerClose(m_controller);
	}
}

bool Input::IsButtonPressed(Buttons button)
{
	return m_buttonsPressed[button];
}

bool Input::IsControllerInitialised()
{
	return m_isControllerInitialised;
}
