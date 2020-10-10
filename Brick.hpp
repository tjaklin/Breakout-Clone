#ifndef BRICK_HPP
#define BRICK_HPP

#include "Sprite.hpp"
#include "RectCollider.hpp"
#include "Sound.hpp"

class Brick{
public:
    Brick(SDL_Point pos, int hp, Sound* hSound, Sound* bSound,
          int bScore, SDL_Texture* texture, SDL_FPoint scale = {1, 1});
    ~Brick();

    void update();
    void render(SDL_Renderer* renderer);
    int onHit();
    void destroy();
    void reset();
    
    const RectCollider& collider() const;
private:
    SDL_Point position_m;
    Sprite sprite_m;
    RectCollider collider_m;
    Sound* hitSound_m;
    Sound* breakSound_m;

    int healthMax_m;
    int healthCurrent_m;
    int breakScore_m;
    bool destroyed_m;
};
#endif // BRICK_HPP
