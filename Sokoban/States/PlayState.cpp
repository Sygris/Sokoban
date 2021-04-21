#include "PlayState.h"

#include "PauseState.h"
#include "MenuState.h"

#include "../Map.h"

PlayState PlayState::s_playState;

void PlayState::Init(Application* application)
{
	m_application = application;

	m_map = new Map(m_application->GetRenderer(), "Assets/Maps/level01.txt", "Assets/Maps/tilesheet.png", 64);
}

void PlayState::Clean()
{
	std::cout << __FUNCTION__ << std::endl;
	
	delete m_map;
	m_map = nullptr;
}

void PlayState::Pause()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PlayState::Resume()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PlayState::HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_application->Quit();

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				m_application->ChangeState(MenuState::Instance());
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void PlayState::Update()
{
}

void PlayState::Draw()
{
	m_map->Render();
}

PlayState::PlayState()
{
}
