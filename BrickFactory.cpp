#include "BrickFactory.hpp"

BrickFactory::BrickFactory(AssetManager* aM) : assetManager_m{aM} {}
BrickFactory::~BrickFactory() {assetManager_m = nullptr;}

void BrickFactory::addNewBrickTemplate(std::string i, std::string tPath, std::string hP,
                                       std::string hSPath, std::string bSPath, int bS)
{
    int realHP;
    if (hP == "Infinite") realHP = std::numeric_limits<int>::max();
    else
        try { realHP = std::stoi(hP); }
        catch (std::invalid_argument) { realHP = 0; }
    
    brickTemplates_m.push_back( BrickTemplate{i, tPath, realHP, hSPath, bSPath, bS} );
}

Brick* BrickFactory::spawnBrickFromTemplate(std::string i, SDL_Point pos, SDL_FPoint scale) const {
    if (assetManager_m == nullptr) return nullptr;
    
    const BrickTemplate* bT{ findBrickTemplate(i) };
    if (!bT) return nullptr;
    Brick* newBrick = nullptr;
    SDL_Texture* texture = assetManager_m->getTexture(bT->texturePath);
    Sound* hitSound = assetManager_m->getSound(bT->hitSoundPath);
    Sound* breakSound = assetManager_m->getSound(bT->breakSoundPath);
    
    newBrick = new Brick(pos, bT->hitPoints, hitSound, breakSound, bT->breakScore, texture, scale);
    return newBrick;
}

const BrickTemplate* BrickFactory::findBrickTemplate(std::string id) const {
    // Ako ne pronađem željeni tip cigle - vratiti će mi se
    // zadani tip cigle "_".
    for (auto& bT : brickTemplates_m) if (bT.id == id) return &bT;
    for (auto& bT : brickTemplates_m) if (bT.id == "_") return &bT;
    return nullptr;
}
