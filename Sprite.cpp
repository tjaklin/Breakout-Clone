#include "Sprite.hpp"

Sprite::Sprite(SDL_Texture* texture, SDL_FPoint scale)
    : texture_m {texture}, dstRect_m{0, 0, 0, 0}
{
    if (!texture_m) {
        SDL_Log("[Sprite] Failed to load texture !\n");
        return;
    }
    SDL_QueryTexture(texture_m, NULL, NULL, &dstRect_m.w, &dstRect_m.h);
    dstRect_m.w *= scale.x;
    dstRect_m.h *= scale.y;
}
Sprite::~Sprite() {}

void Sprite::render(SDL_Renderer* renderer, SDL_Point pos) {
    dstRect_m.x = pos.x;
    dstRect_m.y = pos.y;
    if (texture_m) SDL_RenderCopy(renderer, texture_m, NULL, &dstRect_m);
}
int Sprite::width() const {return dstRect_m.w;}
int Sprite::height() const {return dstRect_m.h;}
bool Sprite::hasTexture() const {return texture_m != nullptr;}
