#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "AssetManager.hpp"

#include "Player.hpp"
#include "Ball.hpp"
#include "BrickFactory.hpp"
#include "Wall.hpp"
#include "Text.hpp"

#include <iostream>
#include <vector>

class Level {
public:
    Level(const SDL_Point pos, const int windowW, const int windowH,
          const int rC, const int cC, const int rS, const int cS,
          AssetManager* aManager, SDL_Texture* texture,
          const BrickFactory& brickFactory,
          std::vector<std::string> bricksLayout,
          SDL_FPoint scale = {1, 1});
    ~Level();

    void update();
    void render();
    void reset();
    
    void pause();
    
    // Ovo koristim za EngineLite::handleEvents() gdje igraču mijenjam velocity.
    Player* const player() const {return player_m;}
private:
    const int rowCount_m;
    const int columnCount_m;
    const int rowSpacing_m;
    const int columnSpacing_m;
    // Za crtanje pozadine Level-a .
    Sprite sprite_m;
    SDL_Point position_m;
    
    bool paused_m;
    bool victory_m;
    bool defeat_m;
    int bricksDestroyed_m;
    AssetManager* assetManager_m;
    SDL_Renderer* renderer_m;
    
    std::vector<std::string> bricksLayout_m;
    std::vector<Brick*> bricks_m;
    Player* player_m;
    Ball* ball_m;
    Wall* walls_m[4];
    
    TTF_Font* font_m;
    Text* guiLevelName_m;
    Text* guiScore_m;
    Text* guiLives_m;
    Text* guiPaused_m;
    Text* guiDefeat_m;
    Text* guiVictory_m;
};
#endif // LEVEL_HPP
