#pragma once

#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <vector>
#include <iostream>

struct GamePad 
{
	bool buttons[SDL_CONTROLLER_BUTTON_MAX];
	int axis[SDL_CONTROLLER_AXIS_MAX];
};

enum Controllers { PLAYER1 = 0, PLAYER2, PLAYER3, PLAYER4 };

const int DEADZONE = 25000;

class Input
{
public:
	Input();
	~Input();

	void InitialiseController();
	void Update();
	void DestroyInput();

	bool IsControllerButtonPressed(Controllers controllerID, SDL_GameControllerButton button);
	bool IsControllerButtonHeld(Controllers controllerID, SDL_GameControllerButton button);
	float GetControllerAxis(Controllers controllerID, SDL_GameControllerAxis axis);

	bool IsControllerInitialised();

private:
	SDL_Event m_event;

	std::vector<SDL_GameController*> m_connectedControllers;
	std::vector<GamePad> m_controllerInputs;
	std::vector<GamePad> m_lastControllerInputs;
	int numGamepads;

	void AddController(int deviceID);
	void RemoveController(int deviceID);
	int ProcessAxisInput(float input);

	bool m_isControllerInitialised { false };
};

