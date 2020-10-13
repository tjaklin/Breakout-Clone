#pragma once

#include "Sprite.h"
#include "RectCollider.h"

class Player {
public:
	Player(SDL_Point pos, int speed, int hp, SDL_Texture* texture, SDL_FPoint scale = { 1, 1 });
	~Player();

	void update();
	void render(SDL_Renderer* renderer);
	void onHit(const CollisionInformation& info);
	void moveTo(SDL_Point destination);
	void moveBy(SDL_Point destination);
	void reset();

	void velocity(SDL_FPoint v);
	void addScore(int s);
	void addLives(int l);

	const RectCollider& collider() const;
	std::string score() const;
	std::string lives() const;
	bool outOfLives() const;
private:
	SDL_Point initialPosition_m;
	SDL_Point position_m;
	Sprite sprite_m;
	RectCollider collider_m;

	int speed_m;
	SDL_FPoint velocity_m;
	int livesMax_m;
	int livesCurrent_m;
	int score_m;
};