#include "CircleCollider.hpp"

CircleCollider::CircleCollider(SDL_Point o, int r, std::string id)
    : Collider{o, id}, radius_m{r}
{}
CircleCollider::~CircleCollider() {}

const CollisionInformation CircleCollider::isColliding(const RectCollider& b) const {
    // Ako RectCollider nije aktivan - ignoriramo ga.
    if ( !b.active() ) return CollisionInformation();
    
    SDL_Point halfRect, cCenter, rCenter;
    halfRect.x = b.width() / 2 ; halfRect.y = b.height() / 2;
    rCenter = b.origin();
    cCenter = origin();
    
    // Oduzmi dvije točke !
    SDL_Point difference{ cCenter.x - rCenter.x, cCenter.y - rCenter.y };
    difference.x = std::clamp(difference.x, -halfRect.x, halfRect.x);
    difference.y = std::clamp(difference.y, -halfRect.y, halfRect.y);
    // Nađi najbližu rubnu točku !
    SDL_Point closestPoint;
    closestPoint.x = rCenter.x + difference.x; closestPoint.y = rCenter.y + difference.y;
    // Udaljenost te točke od kružnice !
    difference.x = closestPoint.x - cCenter.x; difference.y = closestPoint.y - cCenter.y;

    CollisionInformation info;
    if (pointLength(difference) < radius_m) {
        info.isColliding = true;
        info.collidedWith = b.id();
        info.contactPoint.x = difference.x;
        info.contactPoint.y = difference.y;
        // Kada se loptica odbije od splava, želimo joj dati dodatno ubrzanje u određenom smjeru.
        // Taj smjer ovisi o točki na splavu u kojoj se dogodio udarac.
        if (info.collidedWith == "player")
            info.additionalVelocity.x = (closestPoint.x - rCenter.x) / static_cast<float>(halfRect.x*4);
        SDL_Log("[circle collision] with '%s'\n", b.id().c_str());
    }
    return info;
}
int CircleCollider::radius() const {return radius_m;}
