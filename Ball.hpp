#ifndef BALL_H
#define BALL_H

#include "Sprite.hpp"
#include "CircleCollider.hpp"
#include "Sound.hpp"

class Ball {
public:
    Ball(SDL_Point pos, int speed, SDL_Texture* texture, SDL_FPoint scale = {1, 1});
    ~Ball();

    void update();
    void render(SDL_Renderer* renderer);
    void onHit(const CollisionInformation& info);
    void moveTo(SDL_Point destination);
    void moveBy(SDL_Point destination);
    void reset();
    
    const CircleCollider& collider() const;
private:
    SDL_Point initialPosition_m;
    SDL_Point position_m;
    Sprite sprite_m;
    CircleCollider collider_m;
    
    int speed_m;
    SDL_FPoint velocity_m;
};
#endif // BALL_H
