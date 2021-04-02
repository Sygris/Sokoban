#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#if _DEBUG

#define DBG_HALT { __debugbreak(); }
#define DBG_ASSERT_MSG(f, s, m) { if (!(f)) { printf((s), (m)); DBG_HALT; } }

#endif

class Renderer
{
public:
	Renderer();
	~Renderer();

	void SetDisplayColour(int r, int g, int b, int a);
	void Update();
	void Delay(int time);
	void Destroy();

	static SDL_Renderer* GetSDLRenderer() { return m_renderer; };

private:
	SDL_Window* m_window{ nullptr };
	static SDL_Renderer* m_renderer;
};