#include "Application.h"
#include "Renderer.h"
#include "Input.h"
#include "States/MenuState.h"
#include "Audio.h"
#include "Timer.h"

Application::Application()
{
	m_isRunning = true;

	m_renderer = new Renderer();
	m_input = new Input();

	m_sounds = new Audio();
	m_sounds->LoadAudio("Assets/Audio/music/allegro.mp3", 0, MUSIC, 20);
	m_sounds->LoadAudio("Assets/Audio/music/jingle2ch128kbps.mp3", 1, MUSIC, 20);
	m_sounds->LoadAudio("Assets/Audio/sfx/prefix.wav", 0, SFX, 5);

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
	//m_sounds->PlayMusicTrack(0, -1);

	unsigned int a = SDL_GetTicks();
	unsigned int b = SDL_GetTicks();

	int fps = 0;
	uint32_t frameCount = 0;

	double delta = 0;

	while (m_isRunning)
	{
		a = SDL_GetTicks();
		delta = a - b;

		if (delta >= 1000.0f / (double)m_fps)
		{
			b = a;

			fps++;
			frameCount += delta;

			if (frameCount >= 1000.0f)
			{
				frameCount = 0;
				std::cout << fps << std::endl;
				fps = 0;
			}

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

	delete m_input;
	m_input = nullptr;

	delete m_sounds;
	m_sounds = nullptr;

	delete m_renderer;
	m_renderer = nullptr;
}