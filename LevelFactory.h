#pragma once

#include "Level.h"
#include "AssetManager.h"
#include "BrickFactory.h"

#include <vector>
#include <string>
#include <sstream>
#include <tinyxml.h>

struct LevelTemplate {
	std::string id;
	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string texturePath;
	std::vector<std::string> bricksLayout;
};

class LevelFactory {
public:
	LevelFactory(AssetManager* aM);
	~LevelFactory();

	bool addNewLevelTemplate(std::string filePath, std::string id);
	Level* spawnLevelFromTemplate(std::string i, SDL_Point pos,
		const int windowW, const int windowH) const;
	const BrickFactory& getBrickFactory() const;
private:
	const LevelTemplate* findLevelTemplate(std::string id) const;
private:
	AssetManager* assetManager_m;
	BrickFactory brickFactory_m;
	std::vector<LevelTemplate> levelTemplates_m;
};
