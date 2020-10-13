#include "Text.h"

Text::Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Point pos, SDL_Color color)
	: renderer_m{ renderer }, font_m{ font }, rect_m{ pos.x, pos.y },
	color_m{ color }, texture_m{ nullptr }
{}
Text::~Text() { if (texture_m != nullptr) SDL_DestroyTexture(texture_m); }

void Text::render() { SDL_RenderCopy(renderer_m, texture_m, NULL, &rect_m); }
void Text::text(std::string text) {
	if (texture_m != nullptr) SDL_DestroyTexture(texture_m);
	SDL_Surface* surface = TTF_RenderText_Blended(font_m, text.c_str(), color_m);
	texture_m = SDL_CreateTextureFromSurface(renderer_m, surface);
	SDL_QueryTexture(texture_m, nullptr, nullptr, &rect_m.w, &rect_m.h);
	SDL_FreeSurface(surface);
}
