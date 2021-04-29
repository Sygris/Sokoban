#include "Application.h"
#include "Renderer.h"
#include "Input.h"
#include "Audio.h"
#include "Timer.h"

#include "Util/MessageHandler.h"

#include "States/MenuState.h"

#include "UI/Text.h"

Application::Application()
{
	m_isRunning = true;

	m_renderer = new Renderer();
	m_input = new Input();

	m_sounds = new Audio();
	m_sounds->LoadAudio("Assets/Audio/music/mainsong.mp3", 0, MUSIC, 5);
	m_sounds->LoadAudio("Assets/Audio/sfx/win.mp3", 0, SFX, 5);
	m_sounds->LoadAudio("Assets/Audio/sfx/button.mp3", 1, SFX, 10);

	m_textFPS = new Text("Assets/UI/font.ttf", 25);

	ChangeState(MenuState::Instance());
}

Application::~Application()
{
}

void Application::ChangeState(GameState* state)
{
	// Cleanup the current state
	if (!m_states.empty())
	{
		m_states.back()->Clean();
		m_states.pop_back();
	}

	// Stores the state and initialise it
	m_states.push_back(state);
	m_states.back()->Init(this);
}

void Application::PushState(GameState* state)
{
	// Pause current state
	if (!m_states.empty())
	{
		m_states.back()->Pause();
	}

	// Stores the state and initialise it
	m_states.push_back(state);
	m_states.back()->Init(this);
}

void Application::RestartState(GameState* state)
{
	// Clears the entire vector
	if (!m_states.empty())
	{
		for (GameState* state : m_states)
		{
			state->Clean();
		}

		m_states.clear();
	}

	// Stores the state and initialise it
	m_states.push_back(state);
	m_states.back()->Replay(this);
}

void Application::GoToMenuState(GameState* state)
{
	// Clears the entire vector
	if (!m_states.empty())
	{
		for (GameState* state : m_states)
		{
			state->Clean();
		}

		m_states.clear();
	}

	// Stores the state and initialise it
	m_states.push_back(state);
	m_states.back()->Init(this);
}

void Application::PopState()
{
	// cleanup the current state
	if (!m_states.empty())
	{
		m_states.back()->Clean();
		m_states.pop_back();
	}

	// resume previous state
	if (!m_states.empty())
	{
		m_states.back()->Resume();
	}
}

void Application::ChangeFPS()
{
	m_currentFPS++;

	if (m_currentFPS == TotalOfFPS)
	{
		m_currentFPS = 0;
	}

	switch (m_currentFPS)
	{
	case 0:
		m_fps = SIXTY;
		break;
	case 1:
		m_fps = THIRTY;
		break;
	case 2:
		m_fps = HUNDREDTWENTY;
		break;
	default:
		break;
	}
}

void Application::Run()
{
	m_sounds->PlayMusicTrack(0, -1);

#pragma region Controller Warning
	MessageHandler* messageHandler = new MessageHandler();

	m_input->Update();

	while (!m_input->IsControllerInitialised())
	{
		m_input->Update();

		messageHandler->ShowMessage(CONTROLLER_WARNING);
	}
#pragma endregion

#pragma region Instructions
	messageHandler->ShowMessage(INSTRUCTIONS);
#pragma endregion

	while (m_isRunning)
	{
		Timer::GetInstance()->Tick();

		if (Timer::GetInstance()->GetDeltaTime() >= (1 / m_fps))
		{
			m_states.back()->HandleEvents();
			m_states.back()->Update();

			if (m_states.size() > 1)
			{
				for (GameState* state : m_states)
					state->Draw();
			}
			else
			{
				m_states.back()->Draw();
			}

			Timer::GetInstance()->CalculateFPS();

			m_textFPS->DisplayText(std::to_string((int)Timer::GetInstance()->GetLastFPS()), 10, 0, SDL_Color{ 255, 255, 0, 255 }, m_renderer->GetRenderer());

			m_renderer->Update();
		}
	}

	delete messageHandler;
	m_renderer->Destroy();
	Destroy();
}

void Application::Destroy()
{
	while (!m_states.empty())
	{
		m_states.back()->Clean();
		m_states.pop_back();
	}

	delete m_textFPS;
	m_textFPS = nullptr;

	delete m_input;
	m_input = nullptr;

	delete m_sounds;
	m_sounds = nullptr;

	delete m_renderer;
	m_renderer = nullptr;
}