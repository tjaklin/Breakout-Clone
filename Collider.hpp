#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <SDL2/SDL.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <string>

struct CollisionInformation {
    bool isColliding = false;
    std::string collidedWith = "None";
    SDL_Point contactPoint{0, 0};
    SDL_FPoint additionalVelocity{0.0, 0.0};
};

class Collider {
public:
    Collider(SDL_Point o, std::string id);
    ~Collider();
    
    void update(int offsetX, int offsetY);
    void active(bool a);
    void origin(SDL_Point o);

    bool active() const;
    SDL_Point origin() const;
    std::string id() const;
    float pointLength(const SDL_Point& p) const;
protected:
    SDL_Point origin_m;
    std::string id_m;
    bool active_m;
};
#endif // COLLIDER_HPP
