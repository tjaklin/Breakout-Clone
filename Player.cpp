#include "Player.h"

Player::Player(SDL_Point pos, int speed, int hp,
	SDL_Texture* texture, SDL_FPoint scale)
	: livesMax_m{ hp }, livesCurrent_m{ hp }, initialPosition_m{ pos },
	speed_m{ speed }, velocity_m{ 0, 0 }, position_m{ pos },
	score_m{ 0 }, sprite_m{ texture, scale },
	collider_m{
			SDL_Point{
				position_m.x + (sprite_m.width() / 2),
				position_m.y + (sprite_m.height() / 2)
			},
			SDL_Rect{
				position_m.x, position_m.y,
				sprite_m.width(), sprite_m.height()
			},
			"player"
}
{
	SDL_Log("[Player] created!");
	SDL_Log("[Player] pos.x=%d", position_m.x);
	SDL_Log("[Player] collider.origin.x/y=%d/%d", collider_m.origin().x, collider_m.origin().y);
	SDL_Log("[Player] collider.w/h=%d/%d", collider_m.width(), collider_m.height());
}
Player::~Player() {}

void Player::update() {
	int offsetX = static_cast<int>(velocity_m.x * speed_m);
	int offsetY = static_cast<int>(velocity_m.y * speed_m);
	moveBy(SDL_Point{ offsetX, offsetY });
}
void Player::render(SDL_Renderer* renderer) { sprite_m.render(renderer, position_m); }
void Player::onHit(const CollisionInformation& info) {
	// Odziv na udarac !
	int offsetX = ( static_cast<int>(collider_m.width()*0.5f) - std::abs(info.contactPoint.x) );
	if (info.contactPoint.x > 0) offsetX *= -1;
	int offsetY = 0;
	moveBy(SDL_Point{ offsetX, offsetY });
}
void Player::moveTo(SDL_Point destination) {
	SDL_Point distance{ (position_m.x - destination.x)*-1, (position_m.y - destination.y)*-1 };
	moveBy(distance);
}
void Player::moveBy(SDL_Point offset) {
	position_m.x += offset.x;
	position_m.y += offset.y;
	collider_m.update(offset.x, offset.y);
}
void Player::reset() {
	moveTo(initialPosition_m);
	velocity_m.x = 0.0; velocity_m.y = 0.0;
	livesCurrent_m--;
}

void Player::velocity(SDL_FPoint v) { velocity_m = v; }
void Player::addScore(int s) { score_m += s; }
void Player::addLives(int l) { livesCurrent_m += l; }

const RectCollider& Player::collider() const { return collider_m; }
std::string Player::score() const { return std::string("Score: " + std::to_string(score_m)); }
std::string Player::lives() const { return std::string("Lives: " + std::to_string(livesCurrent_m)); }
bool Player::outOfLives() const { return livesCurrent_m < 0; }
