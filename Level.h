#pragma once

#include "AssetManager.h"

#include "Player.h"
#include "Ball.h"
#include "BrickFactory.h"
#include "Wall.h"
#include "Text.h"
#include "Banner.h"

#include <iostream>
#include <vector>

class Level {
public:
	Level(const SDL_Point pos, const int windowW, const int windowH,
		const int rC, const int cC, const int rS, const int cS,
		AssetManager* aManager, SDL_Texture* texture,
		const BrickFactory& brickFactory,
		std::vector<std::string> bricksLayout,
		SDL_FPoint scale = { 1, 1 });
	~Level();

	void update();
	void render();
	void reset();

	void pause();
	bool victory() const;
	bool levelOver() const;
	Player* const player() const { return player_m; }
private:
	const int rowCount_m;
	const int columnCount_m;
	const int rowSpacing_m;
	const int columnSpacing_m;
	// Za crtanje pozadine Level-a .
	Sprite sprite_m;
	SDL_Point position_m;

	bool paused_m;
	bool victory_m;
	bool defeat_m;
	AssetManager* assetManager_m;
	SDL_Renderer* renderer_m;

	std::vector<std::string> bricksLayout_m;
	std::vector<Brick*> bricks_m;
	Player* player_m;
	Ball* ball_m;
	Wall* walls_m[4];

	TTF_Font* font_m;
	Text* guiScore_m;
	Text* guiLives_m;
	Banner* guiPaused_m;
	Banner* guiDefeat_m;
	Banner* guiVictory_m;
};