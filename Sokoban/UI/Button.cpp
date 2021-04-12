#include "Button.h"
#include "../TextureManager.h"

Button::Button(SDL_Renderer* renderer, int x, int y, int height, int width, const std::string& filename)
{
	m_renderer = renderer;
	m_texture = TextureManager::LoadTexture(filename, renderer);

	m_destRect = { x, y, height, width };
}

Button::~Button()
{
	SDL_DestroyTexture(m_texture);
}

void Button::Draw()
{
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_destRect);
}