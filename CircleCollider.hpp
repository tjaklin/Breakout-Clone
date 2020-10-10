#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "RectCollider.hpp"

class CircleCollider : public Collider {
public:
    CircleCollider(SDL_Point o, int r, std::string id);
    ~CircleCollider();
    
    // TODO: Mislim da bi Base klasa Collider morala imati virtualnu
    // ovu metodu isColliding(const Collider& b), gdje je b zapravo neka
    // izvedena klasa čije podatke dobijem preko polimorfizma ?
    // To trenutno ne znam napraviti !
    const CollisionInformation isColliding(const RectCollider& b) const;
    int radius() const;
private:
    int radius_m;
};
#endif // CIRCLE_COLLIDER_H
