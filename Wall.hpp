#ifndef WALL_HPP
#define WALL_HPP

#include "Sprite.hpp"
#include "RectCollider.hpp"

class Wall{
public:
    Wall(SDL_Point pos, SDL_Texture* texture, SDL_FPoint scale = {1, 1},
         const char* colliderId = "wall");
    ~Wall();

    void update();
    void render(SDL_Renderer* renderer);
    const RectCollider& collider() const;
private:
    SDL_Point position_m;
    Sprite sprite_m;
    RectCollider collider_m;
};
#endif // WALL_HPP
