#include "PauseState.h"
#include "../TextureManager.h"

PauseState PauseState::s_pauseState;

void PauseState::Init(Application* application)
{
	m_application = application;

	m_text = TextureManager::LoadTexture("Assets/menu.png", m_application->GetRenderer());
}

void PauseState::Clean()
{
	std::cout << __FUNCTION__ << std::endl;
	SDL_DestroyTexture(m_text);
}

void PauseState::Pause()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PauseState::Resume()
{
	std::cout << __FUNCTION__ << std::endl;
}

void PauseState::HandleEvents()
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
				m_application->PopState();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void PauseState::Update()
{
}

void PauseState::Draw()
{
	SDL_RenderCopy(m_application->GetRenderer(), m_text, NULL, NULL);
}

PauseState::PauseState()
{
}
