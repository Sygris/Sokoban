#include "PauseState.h"

PauseState PauseState::s_pauseState;

void PauseState::Init()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PauseState::Clean()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PauseState::Pause()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PauseState::Resume()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PauseState::HandleEvents(Application* application)
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			application->Quit();

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				application->PopState();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void PauseState::Update(Application* application)
{
	application->GetRenderer()->SetDisplayColour(0, 255, 0, 0);
}

void PauseState::Draw(Application* application)
{
	application->GetRenderer()->Update();
}

PauseState::PauseState()
{
}
