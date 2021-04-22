#include "PlayState.h"

#include "MenuState.h"
#include "PauseState.h"

#include "../Application.h"
#include "../Input.h"
#include "../Audio.h"

#include "../Player.h"

#include "../Map.h"

PlayState PlayState::s_playState;

void PlayState::Init(Application* application)
{
	m_application = application;

	m_map = new Map(m_application->GetRenderer(), "Assets/Maps/level01.txt", "Assets/Maps/tilesheet.png", 64);

	m_object = new Player(
		m_application->GetRenderer(),
		"Assets/Spritesheet/Player.png",
		Vector2D(256, 320),
		Vector2D(64, 64),
		Vector2D(150, 150),
		m_application->GetInput(),
		m_application->GetAudio(),
		m_map,
		PLAYER1
	);
}

void PlayState::Clean()
{
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
	m_application->GetInput()->Update();

	if (!m_application->GetInput()->IsControllerInitialised()) return;

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_X))
	{
		m_application->ChangeState(MenuState::Instance());
	}

	m_object->HandleEvents();
}

void PlayState::Update()
{
	m_object->Update();
}

void PlayState::Draw()
{
	m_map->Render();
	m_object->Draw();
}

PlayState::PlayState()
{
}
