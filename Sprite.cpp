#include "Sprite.hpp"

Sprite::Sprite(SDL_Texture* texture, SDL_FPoint scale) {
    texture_m = texture;
    if (texture_m == nullptr) SDL_Log("[Sprite] Failed to load texture !\n");

    SDL_QueryTexture(texture_m, NULL, NULL, &dstRect_m.w, &dstRect_m.h);
    dstRect_m.w *= scale.x;
    dstRect_m.h *= scale.y;
}
Sprite::~Sprite() {}

void Sprite::render(SDL_Renderer* renderer, SDL_Point pos) {
    dstRect_m.x = pos.x;
    dstRect_m.y = pos.y;
    if (texture_m != nullptr) SDL_RenderCopy(renderer, texture_m, NULL, &dstRect_m);
}
int Sprite::width() const {return dstRect_m.w;}
int Sprite::height() const {return dstRect_m.h;}
