#pragma once

#include "LevelFactory.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class BreakoutGame {
public:
	BreakoutGame();
	~BreakoutGame();

	void handleEvents();
	void update();
	void render();

	void getNextLevel();
	bool running() const;
private:
	SDL_Window* window_m;
	SDL_Renderer* renderer_m;
	bool running_m;

	AssetManager* assetManager_m;
	LevelFactory* levelFactory_m;
	std::vector<Level*> levels_m;
	Level* currentLevel_m;

	Text* guiLevelName_m;
};
