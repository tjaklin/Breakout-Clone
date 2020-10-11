#include "Brick.hpp"

Brick::Brick(SDL_Point pos, int hp, Sound* hSound, Sound* bSound,
             int bScore, SDL_Texture* texture, SDL_FPoint scale)
    :   position_m{pos}, healthMax_m{hp}, healthCurrent_m{hp},
        destroyed_m{false}, breakScore_m{bScore}, 
        sprite_m{texture, scale},
        collider_m{
                SDL_Point{
                    position_m.x + ( sprite_m.width() / 2 ),
                    position_m.y + ( sprite_m.height() / 2 )
                },
                SDL_Rect{
                    position_m.x, position_m.y,
                    sprite_m.width(), sprite_m.height()
                },
                "brick"
            },
        hitSound_m{hSound},
        breakSound_m{bSound}
{    
    SDL_Log("[Brick] created!");
    SDL_Log("[Brick] pos.x=%d", position_m.x);
    SDL_Log("[Brick] collider.origin.x/y=%d/%d", collider_m.origin().x, collider_m.origin().y);
    SDL_Log("[Brick] collider.w/h=%d/%d", collider_m.width(), collider_m.height());
    if (!sprite_m.hasTexture()) destroy();
}
Brick::~Brick() {}

void Brick::update() {
    int offsetX = 0;
    int offsetY = 0;
    position_m.x += offsetX;
    position_m.y += offsetY;
    collider_m.update(offsetX, offsetY);
}
void Brick::render(SDL_Renderer* renderer) {
    if (!destroyed_m)
        sprite_m.render(renderer, position_m);
}
int Brick::onHit() {
    if (--healthCurrent_m <= 0) {
        if (breakSound_m) breakSound_m->play();
        destroy();
        return breakScore_m;
    }
    if (hitSound_m) hitSound_m->play();
    return 0;
}
void Brick::destroy() {
    if (destroyed_m) return;
    destroyed_m = true;
    collider_m.active(false);
}
void Brick::reset() {
    if (!destroyed_m) return;
    destroyed_m = false;
    healthCurrent_m = healthMax_m;
    collider_m.active(true);
}
const RectCollider& Brick::collider() const {return collider_m;}
