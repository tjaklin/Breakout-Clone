#include "Ball.hpp"

Ball::Ball(SDL_Point pos, int speed, SDL_Texture* texture, SDL_FPoint scale)
    : initialPosition_m{pos}, position_m{pos}, speed_m{speed},
      velocity_m{0, 0.25f}, sprite_m{texture, scale},
      collider_m{
            SDL_Point{
                position_m.x + ( sprite_m.width() / 2 ),
                position_m.y + ( sprite_m.height() / 2 )
            },
            std::min(sprite_m.width(), sprite_m.height()) / 2,
            "ball"
        }
{
    SDL_Log("[Ball] created!");
    SDL_Log("[Ball] pos.x=%d", position_m.x);
    SDL_Log("[Ball] collider.origin.x/y=%d/%d", collider_m.origin().x, collider_m.origin().y);
    SDL_Log("[Ball] collider.r=%d", collider_m.radius());
}
Ball::~Ball() {}

void Ball::update() {
    int offsetX = velocity_m.x * speed_m;
    int offsetY = velocity_m.y * speed_m;
    moveBy( SDL_Point{offsetX, offsetY} );    
}
void Ball::render(SDL_Renderer* renderer) {sprite_m.render(renderer, position_m);}
const CircleCollider& Ball::collider() const {return collider_m;}
void Ball::onHit(const CollisionInformation& info) {
    moveBy( SDL_Point{-info.contactPoint.x, -info.contactPoint.y} );
    
    float directionX = std::clamp(-info.contactPoint.x, -1, 1);
    float directionY = std::clamp(-info.contactPoint.y, -1, 1);
    
    float velocityOldX = velocity_m.x;
    float velocityOldY = velocity_m.y;
    
    velocity_m.x = std::clamp(velocity_m.x + directionX, -0.5f, 0.5f) + info.additionalVelocity.x;
    velocity_m.y = std::clamp(velocity_m.y + directionY, -0.5f, 0.5f) + info.additionalVelocity.y;
}
void Ball::reset() {
    moveTo(initialPosition_m);
    velocity_m.x = 0.0; velocity_m.y = 0.25f;
}

void Ball::moveTo(SDL_Point destination) {
    SDL_Point distance{ (position_m.x - destination.x)*-1, (position_m.y - destination.y)*-1 };
    moveBy(distance);
}
void Ball::moveBy(SDL_Point offset) {
    position_m.x += offset.x;
    position_m.y += offset.y;
    collider_m.update(offset.x, offset.y);
}


