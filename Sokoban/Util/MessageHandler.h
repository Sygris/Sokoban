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
		"Instructions - TODO",
		1,
		&button,
		NULL
	};

};
