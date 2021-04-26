#include "PlayState.h"

#include "MenuState.h"
#include "PauseState.h"

#include "../Application.h"
#include "../Input.h"
#include "../Audio.h"

#include "../Player.h"
#include "../Block.h"

#include "../Map.h"

PlayState PlayState::s_playState;

void PlayState::Init(Application* application)
{
	m_application = application;

	m_map = new Map(m_application->GetRenderer(), "Assets/Maps/level01.txt", "Assets/Maps/tilesheet.png", 64);

	m_player = new Player(
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
	for (Block* block : Block::BlockList)
	{
		delete block;
	}

	Block::BlockList.clear();

	delete m_player;
	m_player = nullptr;

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
		return;
	}

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_Y))
	{
		m_application->PushState(PauseState::Instance());
		return;
	}

	m_player->HandleEvents();
}

void PlayState::Update()
{
	m_player->Update();

	for (Block* block : Block::BlockList)
	{
		block->Update();
	}
}

void PlayState::Draw()
{
	m_map->Render();

	for (Block* block : Block::BlockList)
	{
		block->Draw();
	}

	m_player->Draw();
}

void PlayState::Replay()
{
	Application* temp = m_application;

	Clean();
	Init(temp);
}

PlayState::PlayState()
{
}
