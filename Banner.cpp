#include "Banner.hpp"

Banner::Banner(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect bannerRect,
               SDL_Color textColor, SDL_Color bannerColor)
    : renderer_m{renderer}, font_m{font}, textColor_m{textColor},
      bannerColor_m{bannerColor}, texture_m{nullptr}, bannerRect_m{bannerRect}
{}
Banner::~Banner() {if (texture_m != nullptr) SDL_DestroyTexture(texture_m);}

void Banner::render() {
    SDL_SetRenderDrawColor(renderer_m, bannerColor_m.r,
                           bannerColor_m.g, bannerColor_m.b, bannerColor_m.a);
    SDL_RenderFillRect(renderer_m, &bannerRect_m);
    SDL_RenderCopy(renderer_m, texture_m, NULL, &textRect_m);
}
void Banner::text(std::string text) {
    if (texture_m != nullptr) SDL_DestroyTexture(texture_m);
    SDL_Surface* surface = TTF_RenderText_Blended(font_m, text.c_str(), textColor_m);
    texture_m = SDL_CreateTextureFromSurface(renderer_m, surface);
    SDL_QueryTexture(texture_m, nullptr, nullptr, &textRect_m.w, &textRect_m.h);

    int widthDifference = bannerRect_m.w - textRect_m.w;
    bannerRect_m.h = textRect_m.h;
    textRect_m.x = bannerRect_m.x + (widthDifference*0.5f);
    textRect_m.y = bannerRect_m.y;
    
    SDL_FreeSurface(surface);
}
