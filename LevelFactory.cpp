#include "LevelFactory.h"

LevelFactory::LevelFactory(AssetManager* aM)
	: assetManager_m{ aM }, brickFactory_m{ aM }
{
	// Definiranje zadanog tipa cigle.
	brickFactory_m.addNewBrickTemplate("_", "", "0", "", "", 0);
}
LevelFactory::~LevelFactory() {}

bool LevelFactory::addNewLevelTemplate(std::string filePath, std::string id)
{
	TiXmlDocument doc(filePath.c_str());
	doc.LoadFile();
	if (doc.Error()) std::cout << "[LevelFactory] errorMsg = " << doc.ErrorDesc() << "\n";

	TiXmlHandle hDoc{ &doc };
	TiXmlHandle hRoot{ hDoc.FirstChildElement() };

	TiXmlElement* pLevel = hRoot.Element();
	if (!pLevel) {
		std::cout << "[LevelFactory] Failed to read 'Level' element for '" << filePath << "'.\n";
		return false;
	}
	// Èitanje Level èvora !
	int rCount = 0, cCount = 0, rSpacing = 0, cSpacing = 0;
	std::string tPath = "";

	pLevel->QueryIntAttribute("RowCount", &rCount);
	pLevel->QueryIntAttribute("ColumnCount", &cCount);
	pLevel->QueryIntAttribute("RowSpacing", &rSpacing);
	pLevel->QueryIntAttribute("ColumnSpacing", &cSpacing);
	pLevel->QueryStringAttribute("BackgroundTexture", &tPath);

	assetManager_m->loadTexture(tPath);

	// Èitanje bricksLayout vrijednosti !
	TiXmlElement* pBricks = hRoot.FirstChild("Bricks").Element();
	if (!pBricks) {
		std::cout << "[LevelFactory] Failed to read 'Bricks' element for '" << filePath << "'.\n";
		return false;
	}
	std::string bricks = pBricks->GetText();
	std::stringstream ss(bricks);
	std::string item;
	std::vector<std::string> bricksLayout;
	while (std::getline(ss, item, ' ')) {
		bricksLayout.push_back(item);
	}

	// Èitanje BrickTypes atributa !
	TiXmlElement* pBrickType = hRoot.FirstChild("BrickTypes").FirstChild("BrickType").Element();
	if (!pBrickType) {
		std::cout << "[LevelFactory] Failed to read 'BrickTypes' element for '" << filePath << "'.\n";
		return false;
	}

	// Zadaj neku defaultnu vrijednost, za sluèaj da je proèitana vrijednost ilegalna !
	std::string brickID;
	std::string brickTexture, brickHP, brickHitSound = "", brickBreakSound = "";
	int brickScore = 0;

	for (; pBrickType; pBrickType = pBrickType->NextSiblingElement()) {
		if (pBrickType->QueryStringAttribute("Id", &brickID) == TIXML_NO_ATTRIBUTE) {
			std::cout << "[brickTemplate] ERROR: No Id found !\n";
		}
		if (pBrickType->QueryStringAttribute("Texture", &brickTexture) == TIXML_NO_ATTRIBUTE) {
			std::cout << "[brickTemplate] ERROR: No Texture found !\n";
		}
		if (pBrickType->QueryStringAttribute("HitPoints", &brickHP) == TIXML_NO_ATTRIBUTE) {
			std::cout << "[brickTemplate] ERROR: No HitPoints found !\n";
		}
		if (pBrickType->QueryStringAttribute("HitSound", &brickHitSound) == TIXML_NO_ATTRIBUTE) {
			brickHitSound.clear();
		}
		if (pBrickType->QueryStringAttribute("BreakSound", &brickBreakSound) == TIXML_NO_ATTRIBUTE) {
			brickBreakSound.clear();
		}
		if (pBrickType->QueryIntAttribute("BreakScore", &brickScore) == TIXML_NO_ATTRIBUTE) {
			brickScore = 0;
		}

		assetManager_m->loadTexture(brickTexture);
		assetManager_m->loadSound(brickHitSound);
		assetManager_m->loadSound(brickBreakSound);
		brickFactory_m.addNewBrickTemplate(brickID, brickTexture, brickHP,
			brickHitSound, brickBreakSound, brickScore);
	}

	levelTemplates_m.push_back(LevelTemplate{ id, rCount, cCount, rSpacing,
											  cSpacing, tPath, bricksLayout });
	return true;
}

Level* LevelFactory::spawnLevelFromTemplate(std::string i, SDL_Point pos,
	const int windowW, const int windowH) const
{
	if (!assetManager_m) return nullptr;

	const LevelTemplate* lT{ findLevelTemplate(i) };
	if (!lT) return nullptr;
	Level* newLevel = nullptr;
	SDL_Texture* texture = assetManager_m->getTexture(lT->texturePath);

	newLevel = new Level(pos, windowW, windowH, lT->rowCount, lT->columnCount,
		lT->rowSpacing, lT->columnSpacing, assetManager_m,
		texture, brickFactory_m, lT->bricksLayout);
	return newLevel;
}
const BrickFactory& LevelFactory::getBrickFactory() const { return brickFactory_m; }
const LevelTemplate* LevelFactory::findLevelTemplate(std::string id) const {
	for (auto& lT : levelTemplates_m) if (lT.id == id) return &lT;
	return nullptr;
}
