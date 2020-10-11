#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <string>

#include "Sound.hpp"

class AssetManager
{
public:
    AssetManager(SDL_Renderer* renderer);
    ~AssetManager();
    
    bool loadFont(std::string filePath, int fontSize);
    bool loadTexture(std::string filePath, std::string id = std::string(""));
    bool loadSound(std::string filePath, std::string id = std::string(""));
    
    SDL_Renderer* getRenderer();
    SDL_Texture* getTexture(std::string id);
    Sound* getSound(std::string id);
    TTF_Font* getFont();

private:
    std::map<std::string, SDL_Texture*> textures_m;
    std::map<std::string, Sound*> sounds_m;
    TTF_Font* font_m;
    SDL_Renderer* renderer_m;
};
#endif // ASSETMANAGER_H
