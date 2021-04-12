#include "MenuState.h"
#include "PlayState.h"

#include "../Util/MessageHandler.h"

#include "../Input.h"
#include "../Audio.h"
#include "../TextureManager.h"

#include "../UI/Button.h"

#include <iostream>

MenuState MenuState::s_menuState;

MenuState::MenuState()
{
}

void MenuState::Init(Renderer* renderer, Input* input, Audio* audio)
{
	m_input = input;
	m_sounds = audio;
	m_renderer = renderer;

	m_background = TextureManager::LoadTexture("Assets/UI/MainMenuBackground.png", m_renderer->GetRenderer());

	m_buttons.push_back(new Button(m_renderer->GetRenderer(), 380, 250, 200, 80, "Assets/UI/Play.png"));
	m_buttons[PLAY]->AddTexture("Assets/UI/PlayHover.png");

	m_buttons.push_back(new Button(m_renderer->GetRenderer(), 380, 350, 200, 80, "Assets/UI/Options.png"));
	m_buttons[OPTIONS]->AddTexture("Assets/UI/OptionsHover.png");

	m_buttons.push_back(new Button(m_renderer->GetRenderer(), 380, 450, 200, 80, "Assets/UI/Exit.png"));
	m_buttons[EXIT]->AddTexture("Assets/UI/ExitHover.png");

	m_buttons[PLAY]->SetSelected(true); // Sets the button play to start selected
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
		
		if (m_input->IsControllerButtonPressed(controllerID, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
		{
			ChangeSelection(1); // Selection goes down
		}

		if (m_input->IsControllerButtonPressed(controllerID, SDL_CONTROLLER_BUTTON_DPAD_UP))
		{
			ChangeSelection(-1); // Selection goes up
		}

		if (m_input->IsControllerButtonPressed(controllerID, SDL_CONTROLLER_BUTTON_A))
		{
			switch (m_currentButton)
			{
			case PLAY:
				application->ChangeState(PlayState::Instance());
				break;
			case OPTIONS:
				break;
			case EXIT:
				application->Quit();
				break;
			default:
				break;
			}
		}
	}
}

void MenuState::Update(Application* application)
{
	m_renderer->SetDisplayColour(61, 61, 59, 0);
}

void MenuState::Draw(Application* application)
{
	SDL_RenderCopy(m_renderer->GetRenderer(), m_background, NULL, NULL);

	for (auto button : m_buttons)
	{
		button->Draw();
	}

	m_renderer->Update();
}

void MenuState::ChangeSelection(int change)
{
	m_buttons[m_currentButton]->SetSelected(false); // Sets the previous button to its normal behaviour

	m_currentButton += change;

	if (m_currentButton < 0)
	{
		m_currentButton = TOTAL - 1; // Last button in the enum
	}
	else if(m_currentButton >= TOTAL) // Put on testing table that vector out of subscrtion cuz it was only >
	{
		m_currentButton = 0; // First button in the menu
	}

	m_buttons[m_currentButton]->SetSelected(true); // Set the current button hovered
}