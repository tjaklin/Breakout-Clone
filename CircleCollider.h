#pragma once

#include "RectCollider.h"

class CircleCollider : public Collider {
public:
	CircleCollider(SDL_Point o, int r, std::string id);
	~CircleCollider();

	const CollisionInformation isColliding(const RectCollider& b) const;
	int radius() const;
private:
	int radius_m;
};