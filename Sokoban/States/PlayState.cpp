#include "PlayState.h"

#include "MenuState.h"
#include "PauseState.h"

#include "../Application.h"
#include "../Input.h"
#include "../Audio.h"

#include "../Player.h"
#include "../Block.h"

#include "../Map.h"
#include "../Exit.h"
#include "../CollisionHandler.h"

PlayState PlayState::s_playState;

void PlayState::Init(Application* application)
{
	m_application = application;

	messageHandler = new MessageHandler();
}

void PlayState::Clean()
{
	for (Block* block : Block::BlockList)
	{
		delete block;
	}

	Block::BlockList.clear();

	for (Exit* exit : Exit::ExitList)
	{
		delete exit;
	}

	Exit::ExitList.clear();

	for (Player* player : m_players)
	{
		delete player;
	}

	m_players.clear();

	delete m_map;
	m_map = nullptr;
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::HandleEvents()
{
	m_application->GetInput()->Update();

	while (m_application->GetInput()->GetNumOfConnectedControllers() < m_players.size())
	{
		m_application->GetInput()->Update();

		messageHandler->ShowMessage(CONTROLLER_WARNING);
	}

	if (!m_application->GetInput()->IsControllerInitialised()) return;

	if (m_application->GetInput()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_Y))
	{
		m_application->PushState(PauseState::Instance());
		return;
	}

	for (Player* player : m_players)
	{
		player->HandleEvents();
	}
}

void PlayState::Update()
{
	if (Exit::ExitList.empty())
	{
		m_application->PushState(PauseState::Instance());
		PauseState::Instance()->Setup("Assets/UI/WonMenu.png", true); // It setups the pause menu to be a WonMenu (I will do it differently if I had more time)
		return;
	}

	for (Player* player : m_players)
	{
		player->Update();
	}

	for (Block* block : Block::BlockList)
	{
		if (block->IsHome()) continue;

		block->Update();
	}

	for (Exit* exit : Exit::ExitList)
	{
		exit->Update();
	}
}

void PlayState::Draw()
{
	m_map->Render();

	for (Block* block : Block::BlockList)
	{
		block->Draw();
	}

	for (Exit* exit : Exit::ExitList)
	{
		exit->Draw();
	}

	for (Player* player : m_players)
	{
		player->Draw();
	}
}

void PlayState::Replay(Application* application)
{
	Clean();
	Init(application);
	Setup(m_currentMapFilePath);
}

void PlayState::Setup(std::string file)
{
	delete m_map;
	m_map = new Map(m_application->GetRenderer(), file.c_str(), "Assets/Maps/tilesheet.png", 64);
	m_currentMapFilePath = file;
	
	CreatePlayers();
}

PlayState::PlayState()
{
}

void PlayState::CreatePlayers()
{
	std::vector<Vector2D> positions = m_map->GetPlayersPositions();

	for (int i = 0; i < positions.size(); i++)
	{
		std::string playerSprite = "Assets/Spritesheet/Player" + std::to_string(i) + ".png";

		m_players.push_back(new Player(m_application->GetRenderer(), playerSprite, positions[i], Vector2D(64, 64), Vector2D(150, 150), m_application->GetInput(), m_application->GetAudio(), m_map, i));
	}
}
