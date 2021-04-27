#include "Button.h"
#include "../TextureManager.h"

Button::Button(SDL_Renderer* renderer, int x, int y, int height, int width, const std::string& filename)
	: m_renderer{ renderer }, m_destRect{ x, y, height, width }
{
	m_textures.push_back(TextureManager::LoadTexture(filename, renderer));
}

Button::~Button()
{
	for (size_t i = 0; i < m_textures.size(); i++)
	{
		SDL_DestroyTexture(m_textures[i]);
	}
}

void Button::AddTexture(const std::string& filename)
{
	m_textures.push_back(TextureManager::LoadTexture(filename, m_renderer));
}

void Button::SetPosition(int x, int y)
{
	m_destRect.x = x;
	m_destRect.y = y;
}

void Button::Draw()
{
	if (m_selected)
	{
		TextureManager::Draw(m_textures[1], m_renderer, SDL_Rect{}, m_destRect);
	}
	else
	{
		TextureManager::Draw(m_textures[0], m_renderer, SDL_Rect{}, m_destRect);
	}
}
