#pragma once

#include "Brick.h"
#include "AssetManager.h"

#include <vector>
#include <string>
#include <limits>

struct BrickTemplate {
	std::string id;
	std::string texturePath;
	int hitPoints;
	std::string hitSoundPath;
	std::string breakSoundPath;
	int breakScore;
};

class BrickFactory {
public:
	BrickFactory(AssetManager* aM);
	~BrickFactory();

	void addNewBrickTemplate(std::string i, std::string tPath, std::string hP,
		std::string hSPath, std::string bSPath, int bS);
	Brick* spawnBrickFromTemplate(std::string i, SDL_Point pos, SDL_FPoint scale) const;
private:
	const BrickTemplate* findBrickTemplate(std::string id) const;

private:
	AssetManager* assetManager_m;
	std::vector<BrickTemplate> brickTemplates_m;
};