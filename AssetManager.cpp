#include "AssetManager.hpp"
AssetManager::AssetManager(SDL_Renderer* renderer) 
    : renderer_m{renderer}, font_m{nullptr}
{}
AssetManager::~AssetManager() {
    for (auto const& t : textures_m) SDL_DestroyTexture(t.second);
    for (auto const& s : sounds_m) delete s.second;
    textures_m.clear();
    sounds_m.clear();
    if (font_m) TTF_CloseFont(font_m);
}

// LOADER METODE !
bool AssetManager::loadFont(std::string filePath, int fontSize) {
    if (font_m) {TTF_CloseFont(font_m); font_m = nullptr;}
    
    TTF_Font* newFont = nullptr;
    newFont = TTF_OpenFont(filePath.c_str(), fontSize);
    if (newFont == nullptr) {
        std::cout << "[AssetManager] Failed loadFont() on '" << filePath << "' !\n";
        return false;
    } else {
        std::cout << "[AssetManager] Succeded loadFont() on '" << filePath << "' !\n";
        font_m = newFont;
        return true;        
    }
}
bool AssetManager::loadTexture(std::string filePath, std::string id) {
    SDL_Texture* newTexture = nullptr;
    newTexture = IMG_LoadTexture(renderer_m, filePath.c_str());
    if (newTexture == nullptr) {
        std::cout << "[AssetManager] Failed loadTexture() on '" << filePath << "' !\n";
        return false;
    }
    else {
        std::cout << "[AssetManager] Succeded loadTexture() on '" << filePath << "' !\n";
        if (id.empty()) id = filePath;
        textures_m.emplace(id, newTexture);
        return true;        
    }
}
bool AssetManager::loadSound(std::string filePath, std::string id) {
    if (filePath.empty()) return false;
    
    Sound* newSound = nullptr;
    // TODO: Provjeriti ako je filePath valjan !
    newSound = new Sound(filePath);
    if (newSound == nullptr) {
        std::cout << "[AssetManager] Failed loadSound() on '" << filePath << "' !\n";
        return false;
    }
    else {
        std::cout << "[AssetManager] Succeded loadSound() on '" << filePath << "' !\n";
        if (id.empty()) id = filePath;
        sounds_m.emplace(id, newSound);
        return true;        
    }
}

// GETTER METODE !
SDL_Renderer* AssetManager::getRenderer() { return renderer_m; }
SDL_Texture* AssetManager::getTexture(std::string id) {
    SDL_Texture* result = nullptr;
    try {
        result = textures_m.at(id);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "[AssetManager] No texture '" << id << "' to getTexture() !\n";
    }
    return result;
}
Sound* AssetManager::getSound(std::string id) {
    Sound* result = nullptr;
    try {
        result = sounds_m.at(id);
    }
    catch (const std::out_of_range& oor) {
        std::cerr << "[AssetManager] No sound '" << id << "' to getSound() !\n";
    }
    return result;
}
TTF_Font* AssetManager::getFont() {
    return font_m;
}







