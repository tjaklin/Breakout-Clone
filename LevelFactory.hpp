#ifndef LEVEL_FACTORY_HPP
#define LEVEL_FACTORY_HPP

#include "Level.hpp"
#include "AssetManager.hpp"
#include "BrickFactory.hpp"

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
    bool addNewLevelTemplateTest(std::string filePath, std::string id);
    Level* spawnLevelFromTemplate(std::string i, SDL_Point pos, 
                                  const int windowW, const int windowH) const;
    const BrickFactory& getBrickFactory() const;
private:
    const LevelTemplate& findLevelTemplate(std::string id) const;
private:
    AssetManager* assetManager_m;
    BrickFactory brickFactory_m;
    std::vector<LevelTemplate> levelTemplates_m;
};
#endif // LEVEL_FACTORY_HPP
