#include "Application.h"
#include "Renderer.h"
#include "Input.h"
#include "States/MenuState.h"
#include "Audio.h"
#include "Timer.h"

#include "UI/Text.h"

Application::Application()
{
	m_isRunning = true;

	m_renderer = new Renderer();
	m_input = new Input();

	m_sounds = new Audio();
	m_sounds->LoadAudio("Assets/Audio/music/allegro.mp3", 0, MUSIC, 20);
	m_sounds->LoadAudio("Assets/Audio/music/jingle2ch128kbps.mp3", 1, MUSIC, 20);
	m_sounds->LoadAudio("Assets/Audio/sfx/prefix.wav", 0, SFX, 5);

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

void Application::PopState()
{
	// cleanup the current state
	if (!m_states.empty()) {
		m_states.back()->Clean();
		m_states.pop_back();
	}

	// resume previous state
	if (!m_states.empty()) {
		m_states.back()->Resume();
	}
}

void Application::ChangeFPS(float fps)
{
	m_fps = fps;
}

void Application::Run()
{
	m_sounds->PlayMusicTrack(0, -1);

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