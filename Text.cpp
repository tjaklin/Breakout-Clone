#include "Text.hpp"

Text::Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Point pos, std::string text, SDL_Color color)
    :   rect_m{pos.x, pos.y}, text_m{text}, color_m{color}
{
    SDL_Surface* surface = TTF_RenderText_Blended(font, text_m.c_str(), color_m);
    texture_m = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture_m, nullptr, nullptr, &rect_m.w, &rect_m.h);    
    SDL_FreeSurface(surface);
}
Text::~Text() {if (texture_m != nullptr) SDL_DestroyTexture(texture_m);}

void Text::render(SDL_Renderer* renderer) {SDL_RenderCopy(renderer, texture_m, NULL, &rect_m);}

void Text::text(std::string text, SDL_Renderer* renderer, TTF_Font* font) {
    text_m = text;
    if (texture_m != nullptr) SDL_DestroyTexture(texture_m);
    SDL_Surface* surface = TTF_RenderText_Blended(font, text_m.c_str(), color_m);
    texture_m = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture_m, nullptr, nullptr, &rect_m.w, &rect_m.h);
    SDL_FreeSurface(surface);
}
const std::string Text::text() const {return text_m;}
const SDL_Color Text::color() const {return color_m;}
const SDL_Rect Text::rect() const {return rect_m;}
