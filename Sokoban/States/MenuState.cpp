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

	m_buttons.push_back(new Button(m_application->GetRenderer(), 380, 350, 200, 80, "Assets/UI/multiplayer.png"));
	m_buttons[MULTIPLAYER]->AddTexture("Assets/UI/multiplayerHover.png");

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

	m_currentButton = 0;
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
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
		m_application->ChangeFPS();
	}

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_Y))
	{
		m_application->GetAudio()->PlaySFX(0, 0, 0);
	}

	// Maybe next time I should use Callbacks 
	// If the player presses the Button A the code will check which button is currently selected and run its behaviour
	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_A))
	{
		switch (m_currentButton)
		{
		case PLAY:
			m_application->ChangeState(PlayState::Instance());
			PlayState::Instance()->Setup("Assets/Maps/level01.txt");
			break;
		case MULTIPLAYER:
			m_application->PushState(PlayState::Instance());
			PlayState::Instance()->Setup("Assets/Maps/level01Multiplayer.txt");
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
	TextureManager::Draw(m_background, m_application->GetRenderer(), SDL_Rect{}, SDL_Rect{ 0, 0, 960, 720 });

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
	m_application->GetAudio()->PlaySFX(1, 0, 0);
}