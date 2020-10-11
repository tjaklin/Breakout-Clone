#ifndef ENGINE_LITE_HPP
#define ENGINE_LITE_HPP

#include "LevelFactory.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class EngineLite {
public:
    EngineLite();
    ~EngineLite();

    void handleEvents();
    void update(float deltaTime);
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
#endif //ENGINE_LITE_HPP
