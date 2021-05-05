#include "PauseState.h"
#include "PlayState.h"
#include "MenuState.h"

#include "../TextureManager.h"
#include "../Input.h"
#include "../Audio.h"

PauseState PauseState::s_pauseState;

void PauseState::Init(Application* application)
{
	m_application = application;

	m_text = TextureManager::LoadTexture("Assets/UI/PauseMenu.png", m_application->GetRenderer());

	m_buttons.push_back(new Button(m_application->GetRenderer(), 305, 325, 100, 100, "Assets/UI/Home.png"));
	m_buttons[HOME]->AddTexture("Assets/UI/HomeHover.png");

	m_buttons.push_back(new Button(m_application->GetRenderer(), 560, 325, 100, 100, "Assets/UI/replay.png"));
	m_buttons[REPLAY]->AddTexture("Assets/UI/replayHover.png");

	m_buttons[HOME]->SetSelected(true);
}

void PauseState::Clean()
{
	SDL_DestroyTexture(m_text);

	for (Button* button : m_buttons)
	{
		delete button;
		button = nullptr;
	}

	m_buttons.clear();

	m_currentButton = 0; // Resets the button selection to the menu option
	m_isWonMenu = false;
}

void PauseState::Pause()
{
}

void PauseState::Resume()
{
}

void PauseState::HandleEvents()
{
	m_application->GetInput()->Update();

	if (!m_application->GetInput()->IsControllerInitialised()) return;

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		ChangeSelection(1); // Selection goes to the right
	}

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		ChangeSelection(-1); // Selection goes to the left
	}

	// If the pause menu is a WonMenu the player can't close the menu only restart or go back to the menu
	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_Y) && !m_isWonMenu)
	{
		m_application->PopState();
		return;
	}

	// Maybe next time I should use Callbacks 
	// If the player presses the Button A the code will check which button is currently selected and run its behaviour
	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_A))
	{
		switch (m_currentButton)
		{
		case HOME:
			m_application->GoToMenuState(MenuState::Instance());
			break;
		case REPLAY:
			m_application->RestartState(PlayState::Instance());
			break;
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

	for (auto button : m_buttons)
	{
		button->Draw();
	}
}

void PauseState::Setup(std::string file, bool wonMenu)
{
	m_text = TextureManager::LoadTexture(file.c_str(), m_application->GetRenderer());

	m_isWonMenu = wonMenu;

	if (m_isWonMenu)
	{
		m_application->GetAudio()->PlaySFX(0, 0, 0);
	}
}

PauseState::PauseState()
{
}

void PauseState::ChangeSelection(int change)
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
	m_application->GetAudio()->PlaySFX(1, 0, 0);
}
