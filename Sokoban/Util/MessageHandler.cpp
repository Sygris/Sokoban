#include "MessageHandler.h"

namespace Util
{
	MessageHandler::MessageHandler()
	{
	}

	MessageHandler::~MessageHandler()
	{
	}

	void MessageHandler::ShowMessage(messageType type)
	{
		switch (type)
		{
		case INSTRUCTIONS:
			SDL_ShowMessageBox(&ms_instructionsMessage, NULL);
			break;
		case CONTROLLER_WARNING:
			SDL_ShowMessageBox(&ms_controllerMessage, NULL);
			break;
		default:
			break;
		}
	}
}
