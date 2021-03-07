#include "Renderer.h"

Renderer::Renderer()
{
	// Startup
	SDL_Init(SDL_INIT_VIDEO);

	// Create the window
	m_window = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

#if _DEBUG
	DBG_ASSERT_MSG(m_window, "Window initialisation failed: %s\n", SDL_GetError());
#endif

	// Create the renderer
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

#if _DEBUG
	DBG_ASSERT_MSG(m_window, "Renderer initialisation failed: %s\n", SDL_GetError());
#endif
}

Renderer::~Renderer()
{
}

void Renderer::SetDisplayColour(int r, int g, int b, int a)
{
	if (m_renderer)
	{
		int result = SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}
}

void Renderer::Update()
{
	// Clears the Front buffer
	SDL_RenderClear(m_renderer);

	// Flips the back buffer to the front and display
	SDL_RenderPresent(m_renderer);
}

void Renderer::Delay(int time)
{
	SDL_Delay(time);
}

void Renderer::Destroy()
{
	// Do cleanup
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}
}
