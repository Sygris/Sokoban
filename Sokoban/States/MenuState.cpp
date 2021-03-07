#include "MenuState.h"

#include "PlayState.h"

#include <iostream>

MenuState MenuState::s_menuState;

void MenuState::Init()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::Clean()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::Pause()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::Resume()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::HandleEvents(Application* application)
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
				application->ChangeState(PlayState::Instance());
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void MenuState::Update(Application* application)
{
	application->GetRenderer()->SetDisplayColour(255, 0, 0, 0);
}

void MenuState::Draw(Application* application)
{
	application->GetRenderer()->Update();
}

MenuState::MenuState()
{
}
