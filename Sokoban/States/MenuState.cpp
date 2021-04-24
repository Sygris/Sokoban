#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"

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

void MenuState::Init(Application* application)
{
	m_application = application;

	m_background = TextureManager::LoadTexture("Assets/UI/MainMenuBackground.png", m_application->GetRenderer());

	m_buttons.push_back(new Button(m_application->GetRenderer(), 380, 250, 200, 80, "Assets/UI/Play.png"));
	m_buttons[PLAY]->AddTexture("Assets/UI/PlayHover.png");

	m_buttons.push_back(new Button(m_application->GetRenderer(), 380, 350, 200, 80, "Assets/UI/Options.png"));
	m_buttons[OPTIONS]->AddTexture("Assets/UI/OptionsHover.png");

	m_buttons.push_back(new Button(m_application->GetRenderer(), 380, 450, 200, 80, "Assets/UI/Exit.png"));
	m_buttons[EXIT]->AddTexture("Assets/UI/ExitHover.png");

	m_buttons[PLAY]->SetSelected(true); // Sets the button play to start selected
}

void MenuState::Clean()
{
	SDL_DestroyTexture(m_background);

	for (Button* button : m_buttons)
	{
		delete button;
		button = nullptr;
	}

	m_buttons.clear();
}

void MenuState::Pause()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::Resume()
{
	std::cout << __FUNCTION__ << std::endl;
}

void MenuState::HandleEvents()
{
	m_application->GetInput()->Update();

	if (!m_application->GetInput()->IsControllerInitialised()) return;

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		ChangeSelection(1); // Selection goes down
	}

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		ChangeSelection(-1); // Selection goes up
	}

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_B))
	{
		m_application->ChangeFPS(120);
	}

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_Y))
	{
		m_application->GetAudio()->PlaySFX(0, 0, 0);
	}

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_X))
	{
		m_application->ChangeFPS(60);
	}

	// Maybe next time I should use Callbacks 
	// If the player presses the Button A the code will check which button is currently selected and run its behaviour
	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_A))
	{
		switch (m_currentButton)
		{
		case PLAY:
			m_application->ChangeState(PlayState::Instance());
			break;
		case OPTIONS:
			m_application->PushState(PauseState::Instance());
			break;
		case EXIT:
			m_application->Quit();
			break;
		default:
			break;
		}
	}
}

void MenuState::Update()
{
}

void MenuState::Draw()
{
	SDL_RenderCopy(m_application->GetRenderer(), m_background, NULL, NULL);

	for (auto button : m_buttons)
	{
		button->Draw();
	}
}

void MenuState::ChangeSelection(int change)
{
	m_buttons[m_currentButton]->SetSelected(false); // Sets the previous button to its normal behaviour

	m_currentButton += change;

	if (m_currentButton < 0)
	{
		m_currentButton = TOTAL - 1; // Last button in the enum
	}
	else if (m_currentButton >= TOTAL) // Put on testing table that vector out of subscrtion cuz it was only >
	{
		m_currentButton = 0; // First button in the menu
	}

	m_buttons[m_currentButton]->SetSelected(true); // Set the current button hovered
}