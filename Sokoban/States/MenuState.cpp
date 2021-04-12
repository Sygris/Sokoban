#include "MenuState.h"
#include "PlayState.h"

#include "../Util/MessageHandler.h"

#include "../Input.h"
#include "../Audio.h"
#include "../TextureManager.h"

#include "../UI/Button.h"

#include <iostream>

MenuState MenuState::s_menuState;

void MenuState::Init(Renderer* renderer, Input* input, Audio* audio)
{
	m_input = input;
	m_sounds = audio;
	m_renderer = renderer;

	m_button = new Button(m_renderer->GetRenderer(), 220, 150, 200, 80, "Assets/UI/Play.png");
}

void MenuState::Clean()
{
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

	for (size_t i = 0; i < m_input->GetNumOfConnectedControllers(); i++)
	{
		Controllers controllerID = (Controllers)i; // Casts the i to Controllers enum
		
		if (m_input->IsControllerButtonPressed(controllerID, SDL_CONTROLLER_BUTTON_B))
		{
			application->Quit();
		}
		else if (m_input->IsControllerButtonPressed(controllerID, SDL_CONTROLLER_BUTTON_START))
		{
			application->ChangeState(PlayState::Instance());
			return;
		}
		else if (m_input->IsControllerButtonPressed(controllerID, SDL_CONTROLLER_BUTTON_Y))
		{
			m_sounds->PlaySFX(0, 0, 0);
		}
	}
}

void MenuState::Update(Application* application)
{
	m_renderer->SetDisplayColour(61, 61, 59, 0);
}

void MenuState::Draw(Application* application)
{
	m_button->Draw();
	m_renderer->Update();
}

MenuState::MenuState()
{
}
