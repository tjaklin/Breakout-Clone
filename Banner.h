#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Banner {
public:
	Banner(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect bannerRect,
		SDL_Color textColor = SDL_Color{ 255, 255, 255, 255 },
		SDL_Color bannerColor = SDL_Color{ 255, 100, 128, 255 });
	~Banner();

	void render();
	void text(std::string text);
private:
	SDL_Renderer* renderer_m;
	TTF_Font* font_m;
	SDL_Texture* texture_m;
	SDL_Color textColor_m;
	SDL_Color bannerColor_m;
	SDL_Rect bannerRect_m;
	SDL_Rect textRect_m;
};
