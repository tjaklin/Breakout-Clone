#include "Wall.hpp"

Wall::Wall(SDL_Point pos, SDL_Texture* texture, SDL_FPoint scale, const char* colliderId)
    :   position_m{pos},
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
                colliderId
            }
{    
    SDL_Log("[Wall] created!");
    SDL_Log("[Wall] pos.x=%d", position_m.x);
    SDL_Log("[Wall] collider.origin.x/y=%d/%d", collider_m.origin().x, collider_m.origin().y);
    SDL_Log("[Wall] collider.w/h=%d/%d", collider_m.width(), collider_m.height());
}
Wall::~Wall() {}

void Wall::update() {}
void Wall::render(SDL_Renderer* renderer) { sprite_m.render(renderer, position_m); }
const RectCollider& Wall::collider() const {return collider_m;}
