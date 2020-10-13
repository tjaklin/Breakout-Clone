#pragma once

#include "Sprite.h"
#include "RectCollider.h"
#include "Sound.h"

class Brick {
public:
	Brick(SDL_Point pos, int hp, Sound* hSound, Sound* bSound,
		int bScore, SDL_Texture* texture, SDL_FPoint scale = { 1, 1 });
	~Brick();

	void update();
	void render(SDL_Renderer* renderer);
	int onHit();
	void destroy();

	const RectCollider& collider() const;
	bool destroyed() const;
private:
	SDL_Point position_m;
	Sprite sprite_m;
	RectCollider collider_m;
	Sound* hitSound_m;
	Sound* breakSound_m;

	int healthMax_m;
	int healthCurrent_m;
	int breakScore_m;
	bool destroyed_m;
};