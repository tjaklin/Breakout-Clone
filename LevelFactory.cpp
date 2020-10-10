#include "LevelFactory.hpp"

LevelFactory::LevelFactory(AssetManager* aM)
    : assetManager_m{aM}, brickFactory_m{aM}
{}
LevelFactory::~LevelFactory() {assetManager_m = nullptr;}

bool LevelFactory::addNewLevelTemplate(std::string filePath, std::string id)
{
    // TODO: Tu sad učitati iz 'filepath' cijeli Level i stvoriti novi LevelTemplate i
    // pripadajuće BrickTemplate-ove !
    // Također, loadati sve potrebne Assete u AssetManager !    
    TiXmlDocument doc(filePath);
    bool status = doc.LoadFile();
    
    TiXmlHandle hDoc{&doc};
    TiXmlHandle hRoot{hDoc.FirstChildElement()};
    
    TiXmlElement* pLevel = hRoot.Element();
    if (!pLevel) {
        std::cout<< "Failed to read 'Level' element !\n";
        return false;
    }
    
    // Zadaj neku defaultnu vrijednost, za slučaj da je pročitana vrijednost ilegalna !
    int rCount = 0, cCount = 0, rSpacing = 0, cSpacing = 0;
    std::string tPath = "";
    
    pLevel->QueryIntAttribute("RowCount", &rCount);
    pLevel->QueryIntAttribute("ColumnCount", &cCount);
    pLevel->QueryIntAttribute("RowSpacing", &rSpacing);
    pLevel->QueryIntAttribute("ColumnSpacing", &cSpacing);
    pLevel->QueryStringAttribute("BackgroundTexture", &tPath);
    
    // Probaj loadati teksturu !
    assetManager_m->loadTexture(tPath);
    
    // Čitanje bricksLayout vrijednosti !
    TiXmlElement* pBricks = hRoot.FirstChild("Bricks").Element();
    
    if (!pBricks) {
        std::cout << "Failed to read 'Bricks' element !\n";
        return false;
    }
    std::string bricks = pBricks->GetText();
    std::stringstream ss(bricks);
    std::string item;
    std::vector<std::string> bricksLayout;
    while (std::getline(ss, item, ' ')) {
        bricksLayout.push_back(item);
    }

    // Čitanje BrickTypes atributa !
    TiXmlElement* pBrickType = hRoot.FirstChild("BrickTypes").FirstChild("BrickType").Element();

    if (!pBrickType) {
        std::cout << "Failed to read a 'BrickTypes' element !\n";
        return false;
    }

    // Zadaj neku defaultnu vrijednost, za slučaj da je pročitana vrijednost ilegalna !
    std::string brickID;
    std::string brickTexture, brickHP, brickHitSound = "", brickBreakSound = "";
    int brickScore = 0;

    for (; pBrickType; pBrickType=pBrickType->NextSiblingElement()) {
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
    
    // TODO: Tu očekivati moguću pogrešku kada se 'i' već koristi.
    // Ali prvo pretvoriti ovaj vector u map !
//    try {
        levelTemplates_m.push_back( LevelTemplate{id, rCount, cCount, rSpacing,
                                                  cSpacing, tPath, bricksLayout} );
//    }
}

bool LevelFactory::addNewLevelTemplateTest(std::string filePath, std::string id) {
    // TODO: Tu sad učitati iz 'filepath' cijeli Level i stvoriti novi LevelTemplate i
    // pripadajuće BrickTemplate-ove !
    // Također, loadati sve potrebne Assete u AssetManager !    
    TiXmlDocument doc(filePath);
    bool status = doc.LoadFile();
    
    TiXmlHandle hDoc{&doc};
    TiXmlHandle hRoot{hDoc.FirstChildElement()};
    
    TiXmlElement* pLevel = hRoot.Element();
    if (!pLevel) {
        std::cout<< "Failed to read 'Level' element !\n";
        return false;
    }
    
    // Zadaj neku defaultnu vrijednost, za slučaj da je pročitana vrijednost ilegalna !
    int rCount = 30, cCount = 20, rSpacing = 3, cSpacing = 3;
    std::string tPath = "Textures/Boards/Board_01.bmp";
    
//     pLevel->QueryIntAttribute("RowCount", &rCount);
//     pLevel->QueryIntAttribute("ColumnCount", &cCount);
//     pLevel->QueryIntAttribute("RowSpacing", &rSpacing);
//     pLevel->QueryIntAttribute("ColumnSpacing", &cSpacing);
//     pLevel->QueryStringAttribute("BackgroundTexture", &tPath);
    
    // Probaj loadati teksturu !
//    assetManager_m->loadTexture(tPath);
    assetManager_m->loadTexture(tPath);
    
    // Čitanje bricksLayout vrijednosti !
    TiXmlElement* pBricks = hRoot.FirstChild("Bricks").Element();
    
    if (!pBricks) {
        std::cout << "Failed to read 'Bricks' element !\n";
        return false;
    }
//    std::string bricks = pBricks->GetText();
    std::string bricks = "H H H H H H H H H H H H H H H H H H H H M M I I M M M M M M M M M M M M I I M M S S S S S S S S S S S S S S S S S S S S";
    std::stringstream ss(bricks);
    std::string item;
    std::vector<std::string> bricksLayout;
    while (std::getline(ss, item, ' ')) {
        bricksLayout.push_back(item);
    }
    
    // Čitanje BrickTypes atributa !
    TiXmlElement* pBrickType = hRoot.FirstChild("BrickTypes").FirstChild("BrickType").Element();
    
    if (!pBrickType) {
        std::cout << "Failed to read a 'BrickTypes' element !\n";
        return false;
    }
    
    // Zadaj neku defaultnu vrijednost, za slučaj da je pročitana vrijednost ilegalna !
    std::string brickID;
    std::string brickTexture, brickHP, brickHitSound = "", brickBreakSound = "";
    int brickScore = 0;
/*
    for (; pBrickType; pBrickType=pBrickType->NextSiblingElement()) {
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
        
        assetManager_m->loadTexture(brickTexture);
        assetManager_m->loadSound(brickHitSound);
        assetManager_m->loadSound(brickBreakSound);
        brickFactory_m.addNewBrickTemplate(brickID, brickTexture, brickHP,
                                brickHitSound, brickBreakSound, brickScore);
*/    
    // OVO UMJESTO FOR LOOP-a !
    brickID = "S";
    brickTexture = "Textures/Bricks/Soft.bmp";
    brickHP = "1";
    brickHitSound = "Sounds/Hit_01.wav";
    brickBreakSound = "Sounds/Break_01.wav";
    brickScore = 50;
    
    assetManager_m->loadTexture(brickTexture);
    assetManager_m->loadSound(brickHitSound);
    assetManager_m->loadSound(brickBreakSound);
    brickFactory_m.addNewBrickTemplate(brickID, brickTexture, brickHP,
                            brickHitSound, brickBreakSound, brickScore);

    brickID = "M";
    brickTexture = "Textures/Bricks/Medium.bmp";
    brickHP = "2";
    brickHitSound = "Sounds/Hit_02.wav";
    brickBreakSound = "Sounds/Break_02.wav";
    brickScore = 100;
    
    assetManager_m->loadTexture(brickTexture);
    assetManager_m->loadSound(brickHitSound);
    assetManager_m->loadSound(brickBreakSound);
    brickFactory_m.addNewBrickTemplate(brickID, brickTexture, brickHP,
                            brickHitSound, brickBreakSound, brickScore);

    brickID = "H";
    brickTexture = "Textures/Bricks/Hard.bmp";
    brickHP = "3";
    brickHitSound = "Sounds/Hit_03.wav";
    brickBreakSound = "Sounds/Break_03.wav";
    brickScore = 150;
    
    assetManager_m->loadTexture(brickTexture);
    assetManager_m->loadSound(brickHitSound);
    assetManager_m->loadSound(brickBreakSound);
    brickFactory_m.addNewBrickTemplate(brickID, brickTexture, brickHP,
                            brickHitSound, brickBreakSound, brickScore);
    brickID = "I";
    brickTexture = "Textures/Bricks/Impenetrable.bmp";
    brickHP = "Infinite";
    brickHitSound = "Sounds/Hit_04.wav";
    brickBreakSound.clear();
    brickScore = 0;
    
    assetManager_m->loadTexture(brickTexture);
    assetManager_m->loadSound(brickHitSound);
    assetManager_m->loadSound(brickBreakSound);
    brickFactory_m.addNewBrickTemplate(brickID, brickTexture, brickHP,
                            brickHitSound, brickBreakSound, brickScore);
    
    // TODO: Tu očekivati moguću pogrešku kada se 'i' već koristi.
    // Ali prvo pretvoriti ovaj vector u map !
//    try {
        levelTemplates_m.push_back( LevelTemplate{id, rCount, cCount, rSpacing,
                                                  cSpacing, tPath, bricksLayout} );
//    }
}

Level* LevelFactory::spawnLevelFromTemplate(std::string i, SDL_Point pos,
                                            const int windowW, const int windowH) const
{
    // TODO: Provjeru ovog 'i' stringa, jer moguće da pošaljem nepostojeći id !
    std::cout << "[levelFactory] spawn():\n";
    std::cout << "\tid = '" << i << "'.\n";
    std::cout << "\tpos.x/y = " << pos.x << "/" << pos.y << ".\n";
    std::cout << "\twindow.w/h = " << windowW << "/" << windowH << ".\n";
    if (assetManager_m == nullptr) return nullptr;
    
    const LevelTemplate& lT{ findLevelTemplate(i) };
    Level* newLevel = nullptr;
    SDL_Texture* texture = assetManager_m->getTexture(lT.texturePath);
    
    newLevel = new Level(pos, windowW, windowH, lT.rowCount, lT.columnCount,
                         lT.rowSpacing, lT.columnSpacing, assetManager_m,
                         texture, brickFactory_m, lT.bricksLayout);
    return newLevel;
}
const BrickFactory& LevelFactory::getBrickFactory() const {return brickFactory_m;}

const LevelTemplate& LevelFactory::findLevelTemplate(std::string id) const {
    std::cout << "[levelFactory] findLevelTemplate.size() = " << levelTemplates_m.size() << "\n";
    for (auto& lT : levelTemplates_m) if (lT.id == id) return lT;
}
