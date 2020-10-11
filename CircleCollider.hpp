#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "RectCollider.hpp"

class CircleCollider : public Collider {
public:
    CircleCollider(SDL_Point o, int r, std::string id);
    ~CircleCollider();
    
    const CollisionInformation isColliding(const RectCollider& b) const;
    int radius() const;
private:
    int radius_m;
};
#endif // CIRCLE_COLLIDER_H
