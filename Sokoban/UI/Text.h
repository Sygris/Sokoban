#pragma once

#include <string>
#include <SDL_ttf.h>

class Vector2D;

class Text
{
public:
	Text(std::string fontPath, int ptSize);
	~Text();

	void DisplayText(std::string text, int x, int y, SDL_Color color, SDL_Renderer* renderer);

private:
	TTF_Font* m_font{ nullptr };
};

