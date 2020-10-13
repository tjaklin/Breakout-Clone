#include "Collider.h"

Collider::Collider(SDL_Point o, std::string i)
	: origin_m{ o }, id_m{ i }, active_m{ true }
{}
Collider::~Collider() {}

void Collider::origin(SDL_Point o) { origin_m = o; }
void Collider::update(int offsetX, int offsetY) { origin_m.x += offsetX; origin_m.y += offsetY; }
void Collider::active(bool a) { active_m = a; }

bool Collider::active() const { return active_m; }
SDL_Point Collider::origin() const { return origin_m; }
std::string Collider::id() const { return id_m; }

float Collider::pointLength(const SDL_Point& p) const { return static_cast<float>(std::sqrt(p.x * p.x + p.y * p.y)); }
