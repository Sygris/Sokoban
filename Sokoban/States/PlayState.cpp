#include "PlayState.h"

#include "PauseState.h"

PlayState PlayState::s_playState;

void PlayState::Init()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PlayState::Clean()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PlayState::Pause()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PlayState::Resume()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PlayState::HandleEvents(Application* application)
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
				application->PushState(PauseState::Instance());
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void PlayState::Update(Application* application)
{
	application->GetRenderer()->SetDisplayColour(0, 0, 255, 0);
}

void PlayState::Draw(Application* application)
{
	application->GetRenderer()->Update();
}

PlayState::PlayState()
{
}
