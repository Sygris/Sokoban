#include "Application.h"
#include "Renderer.h"
#include "Input.h"
#include "States/MenuState.h"
#include "Audio.h"

Application::Application()
{
	m_isRunning = true;

	m_renderer = new Renderer();
	m_input = new Input();
	m_timer = new Timer();

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
	m_states.back()->Init(m_renderer, m_input, m_sounds);
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
	m_states.back()->Init(m_renderer, m_input, m_sounds);
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
	double delta = 0;

	while (m_isRunning)
	{
		a = SDL_GetTicks();
		delta = a - b;

		if (delta >= 1000 / m_fps)
		{
			b = a;
			m_states.back()->HandleEvents(this);
			m_states.back()->Update(this);
			m_states.back()->Draw(this);
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

	delete m_timer;
	m_timer = nullptr;

	delete m_input;
	m_input = nullptr;

	delete m_sounds;
	m_sounds = nullptr;

	delete m_renderer;
	m_renderer = nullptr;
}
