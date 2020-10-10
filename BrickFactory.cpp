#include "BrickFactory.hpp"

BrickFactory::BrickFactory(AssetManager* aM) {
    assetManager_m = aM;
    // TODO: Ovu liniju ispod omogućiti !
    //addNewBrickTemplate("_", nullptr, nullptr, nullptr, nullptr, nullptr);
}
BrickFactory::~BrickFactory() {assetManager_m = nullptr;}

void BrickFactory::addNewBrickTemplate(std::string i, std::string tPath, std::string hP,
                                       std::string hSPath, std::string bSPath, int bS)
{
    // TODO: Tu očekivati moguću pogrešku kada se 'i' već koristi.
    // Ali prvo pretvoriti ovaj vector u map !
//    try {
    int realHP;
    if (hP == "Infinite") realHP = std::numeric_limits<int>::max();
    else realHP = std::stoi(hP);
    
    brickTemplates_m.push_back( BrickTemplate{i, tPath, realHP, hSPath, bSPath, bS} );
//    }
}

Brick* BrickFactory::spawnBrickFromTemplate(std::string i, SDL_Point pos, SDL_FPoint scale) const {
    // TODO: Provjeru ovog 'i' stringa, jer moguće da pošaljem nepostojeći id !
    if (assetManager_m == nullptr) return nullptr;
    
    const BrickTemplate& bT{ findBrickTemplate(i) };
    SDL_Texture* texture = assetManager_m->getTexture(bT.texturePath);
    Sound* hitSound = assetManager_m->getSound(bT.hitSoundPath);
    Sound* breakSound = assetManager_m->getSound(bT.breakSoundPath);
    
    return new Brick(pos, bT.hitPoints, hitSound, breakSound, bT.breakScore, texture, scale);
}

const BrickTemplate& BrickFactory::findBrickTemplate(std::string id) const {
    std::cout << "[BrickFactory] findBrickTemplate.size() = " << brickTemplates_m.size() << "\n";
    for (auto& bT : brickTemplates_m) if (bT.id == id) return bT;
    // TODO: Ovaj drugi for loop neka bude 'u slučaju da ne nađem svoj id'.
    // Tada u ovom loop-u tražim defaultni '_' brick !
    //for (auto& bT : brickTemplates_m) if (bT.id == "_") return bT;
}
/*
std::vector<Brick*> BrickFactory::spawnBricksFromLayout(std::vector<std::string> bricksLayout) {
    // TODO: Provjeri je li primljeni parametar legalan !
    std::vector<Brick*>
    for (auto& id : bricksLayout) {
        spawnBrickFromTemplate(id)
    }
}
*/
