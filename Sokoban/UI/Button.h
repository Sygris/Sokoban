#pragma once

#include <SDL.h>
#include <string>

class Button
{
public:
	Button(SDL_Renderer* renderer, int x, int y, int height, int width, const std::string& filename);
	~Button();

	void Draw();

private:
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect, m_destRect;
	bool selected;

	SDL_Renderer* m_renderer;
};

