#pragma once

#include <SDL.h>

enum messageType
{
	INSTRUCTIONS, CONTROLLER_WARNING, totalOfMessageTypes
};

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	void ShowMessage(messageType type);

private:
	const SDL_MessageBoxButtonData button = {
		SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "OK"
	};

	const SDL_MessageBoxData ms_controllerMessage = {
		SDL_MESSAGEBOX_ERROR,
		NULL,
		"Controller Error",
		"Controller not connected!! - \nInsert controller and press Escape",
		0,
		0,
		NULL
	};

	const SDL_MessageBoxData ms_instructionsMessage = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL,
		"Controller instructions",
		"Use the DPAD to move\nPress A to select\nPress Y to open the pause menu\nPress B to toggle the FPS between 30, 60 and 120FPS",
		1,
		&button,
		NULL
	};

};
