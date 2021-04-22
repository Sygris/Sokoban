#pragma once

#include <SDL.h>
#include <vector>
#include "Vector2D.h"

class GameObject
{
public:
	GameObject(SDL_Renderer* renderer, const std::string& filename, Vector2D position, Vector2D size);
	~GameObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	inline const Vector2D GetPosition() { return m_position; }
	inline const Vector2D GetSize() { return m_size; }

protected:
	SDL_Renderer* m_renderer{ nullptr };

	SDL_Texture* m_texture{ nullptr };
	SDL_Rect m_srcRect{ NULL }, m_dstRect{ NULL };

	Vector2D m_position;
	Vector2D m_size;
};

