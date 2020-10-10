#ifndef RECT_COLLIDER_H
#define RECT_COLLIDER_H

#include "Collider.hpp"

class RectCollider : public Collider {
public:
    RectCollider(SDL_Point o, SDL_Rect r, std::string id);
    ~RectCollider();
    
    const CollisionInformation isColliding(const RectCollider& b) const;
    
    int width() const;
    int height() const;
private:
    SDL_Rect rect_m;
};
#endif // RECT_COLLIDER_H
