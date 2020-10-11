#include "RectCollider.hpp"

RectCollider::RectCollider(SDL_Point o, SDL_Rect r, std::string id)
    : Collider{o, id}, rect_m{r}
{}
RectCollider::~RectCollider() {}

const CollisionInformation RectCollider::isColliding(const RectCollider& b) const {

    if (!b.active()) return CollisionInformation();
    
    SDL_Point aCenter, bCenter, bHalfDimensions;
    aCenter = origin();
    bCenter = b.origin();
//    std::cout << "aCenter.x/y = " << aCenter.x << " / " << aCenter.y << "\n";
//    std::cout << "bCenter.x/y = " << bCenter.x << " / " << bCenter.y << "\n";

    bHalfDimensions.x = b.width() / 2 ; bHalfDimensions.y = b.height() / 2;
//    std::cout << "bHalfDimensions.x/y = " << bHalfDimensions.x << " / " << bHalfDimensions.y << "\n";
    
    SDL_Point difference{ aCenter.x - bCenter.x, aCenter.y - bCenter.y };
    difference.x = std::clamp(difference.x, -bHalfDimensions.x, bHalfDimensions.x);
    difference.y = std::clamp(difference.y, -bHalfDimensions.y, bHalfDimensions.y);
//    std::cout << "difference.x/y = " << difference.x << " / " << difference.y << "\n";
    
    SDL_Point closestPoint;
    closestPoint.x = bCenter.x + difference.x; closestPoint.y = bCenter.y + difference.y;
    difference.x = closestPoint.x - aCenter.x; difference.y = closestPoint.y - aCenter.y;
//    std::cout << "closestPoint.x/y = " << closestPoint.x << " / " << closestPoint.y << "\n";
    
    bool collisionX = std::abs(difference.x) <= (rect_m.w / 2);
    bool collisionY = std::abs(difference.y) <= (rect_m.h / 2);
//    std::cout << collisionX << " = " << std::abs(difference.x) << " <= " << (rect_m.w / 2) << "\n";
//    std::cout << collisionY << " = " << std::abs(difference.y) << " <= " << (rect_m.h / 2) << "\n";
    
    CollisionInformation info;
    if (collisionX && collisionY) {
        info.isColliding = true;
        info.collidedWith = b.id();
        info.contactPoint.x = difference.x;
        info.contactPoint.y = difference.y;
        
        info.additionalVelocity.x = 0;
        info.additionalVelocity.y = 0;
        SDL_Log("[rect collision] with '%s'\n", b.id().c_str());
    }
    return info;
}

int RectCollider::width() const {return rect_m.w;}
int RectCollider::height() const {return rect_m.h;}

