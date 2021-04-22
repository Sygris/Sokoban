#include "Text.h"

#include "../Vector2D.h"

Text::Text(std::string filePath, int ptSize)
{
	if (TTF_WasInit() == 0)
	{
		TTF_Init();
	}

	m_font = TTF_OpenFont(filePath.c_str(), ptSize);

#if _DEBUG
	SDL_assert(m_font != nullptr);
#endif // _DEBUG
}

Text::~Text()
{
	TTF_CloseFont(m_font);
	TTF_Quit();
}

void Text::DisplayText(std::string text, int x, int y, SDL_Color color, SDL_Renderer* renderer)
{
	SDL_Surface* surface{ nullptr };
	SDL_Texture* texture{ nullptr };
	SDL_Rect textRect{};

	int TextWidth, TextHeight = 0;

	surface = TTF_RenderText_Blended(m_font, text.c_str(), color);

#if _DEBUG
	SDL_assert(surface != nullptr);
#endif // _DEBUG

	texture = SDL_CreateTextureFromSurface(renderer, surface);

#if _DEBUG
	SDL_assert(texture != nullptr);
#endif // _DEBUG

	SDL_QueryTexture(texture, NULL, NULL, &TextWidth, &TextHeight);

	textRect = { x, y, TextWidth, TextHeight };

	SDL_RenderCopy(renderer, texture, NULL, &textRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}