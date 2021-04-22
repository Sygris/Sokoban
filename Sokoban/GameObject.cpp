#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size)
	: m_renderer{ renderer }, m_position{ position }, m_size{ size }
{
	m_texture = TextureManager::LoadTexture(filename.c_str(), m_renderer);

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = (int)m_size.x;
	m_srcRect.h = (int)m_size.y;

	m_dstRect.x = (int)m_position.x;
	m_dstRect.y = (int)m_position.y;
	m_dstRect.w = (int)m_size.x;
	m_dstRect.h = (int)m_size.y;
}

GameObject::~GameObject()
{
	SDL_DestroyTexture(m_texture);
}
