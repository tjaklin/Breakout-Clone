#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite {
public:
	Sprite(SDL_Texture* texture, SDL_FPoint scale);
	~Sprite();

	void render(SDL_Renderer* renderer, SDL_Point pos);

	int width() const;
	int height() const;
	bool hasTexture() const;
protected:
	SDL_Texture* texture_m;
	SDL_Rect dstRect_m;
};
