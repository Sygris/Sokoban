#include "MenuState.h"
#include "PlayState.h"

#include "../Util/MessageHandler.h"

#include "../Input.h"
#include "../Audio.h"
#include "../TextureManager.h"

#include <iostream>

MenuState MenuState::s_menuState;

void MenuState::Init()
{
	m_input = new Input();
	m_texture = TextureManager::LoadTexture("Assets/arrow.png", Renderer::GetSDLRenderer());
}

void MenuState::Clean()
{
	delete m_input;
	m_input = nullptr;
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
	m_input->Update();

	if (!m_input->IsControllerInitialised()) return;

	if (m_input->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_B))
	{
		application->Quit();
	}
	else if (m_input->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_A))
	{
		application->ChangeState(PlayState::Instance());
	}
	else if (m_input->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_Y))
	{
		application->m_sounds->PlaySFX(0, 0, 0);
	}
	else if (m_input->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_X))
	{
		application->m_sounds->FadeMusicTrack(1, 1, 200);
	}
}

void MenuState::Update(Application* application)
{
	application->GetRenderer()->SetDisplayColour(255, 0, 0, 0);
}

void MenuState::Draw(Application* application)
{
	//application->GetRenderer()->Update();

		// Clears the Front buffer
	SDL_RenderClear(Renderer::GetSDLRenderer());

	SDL_RenderCopy(Renderer::GetSDLRenderer(), m_texture, NULL, NULL);

	// Flips the back buffer to the front and display
	SDL_RenderPresent(Renderer::GetSDLRenderer());
}

MenuState::MenuState()
{
}
