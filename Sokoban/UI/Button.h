#pragma once

#include <SDL.h>
#include <string>
#include <vector>

class Button
{
public:
	Button(SDL_Renderer* renderer, int x, int y, int height, int width, const std::string& filename);
	~Button();

	void AddTexture(const std::string &filename);
	void SetPosition(int x, int y);

	void SetSelected(bool isSelected) { m_selected = isSelected; }
	
	void Draw();

private:
	std::vector<SDL_Texture*> m_textures;
	SDL_Rect m_destRect;

	bool m_selected{ false };

	SDL_Renderer* m_renderer{ nullptr };
};

