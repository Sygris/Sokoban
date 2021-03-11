#pragma once

#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <iostream>

enum Buttons 
{
	UP, DOWN, LEFT, RIGHT, A, X, Y, B, L1, R1, SIZE
};

class Input
{
public:
	Input();
	~Input();

	void InitialiseController();
	void Update();
	void DestroyInput();
	bool IsButtonPressed(Buttons button);
	bool IsControllerInitialised();

private:
	SDL_Event m_event;
	bool m_buttonsPressed[SIZE] { NULL };
	SDL_GameController* m_controller { nullptr };
	bool m_isControllerInitialised { false };
};

