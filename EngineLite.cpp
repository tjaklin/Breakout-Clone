#include "EngineLite.hpp"

EngineLite::EngineLite()
   :    running_m{true}, assetManager_m{nullptr},
        levelFactory_m{nullptr}, currentLevel_m{nullptr},
        guiLevelName_m{nullptr}, window_m{nullptr},
        renderer_m{nullptr}
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cout << "[engine] Failed on SDL_Init() !\n";
        return;
    }
    if (TTF_Init() != 0 ) {
        std::cout << "[engine] Failed on TTF_Init() !\n";
        return;
    }
    
    const int windowW = 1024;
    const int windowH = 768;
    
    window_m = SDL_CreateWindow("EngineLite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                windowW, windowH, SDL_WINDOW_SHOWN);
    if (window_m == nullptr) {
        std::cout << "[engine] Failed on SDL_CreateWindow() !\n";
        return;
    }
    renderer_m = SDL_CreateRenderer(window_m, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_m == nullptr) {
        std::cout << "[engine] Failed on SDL_CreateRenderer() !\n";
        return;
    }
    assetManager_m = new AssetManager(renderer_m);
    if (assetManager_m == nullptr) {
        std::cout << "[engine] Failed on new AssetManager(...) !\n";
        return;
    }
    int fontSize = 0.025 * windowW;
    if (!assetManager_m->loadFont("./myFont.ttf", fontSize)) std::cout << "loadFont() Failed !\n";
    if (!assetManager_m->loadTexture("background.bmp", "defaultBackground"))
        std::cout << "loadTexture('background.bmp') Failed !\n";
    if(!assetManager_m->loadTexture("player80.bmp", "defaultPlayer"))
        std::cout << "loadTexture('player80.bmp') Failed !\n";
    if(!assetManager_m->loadTexture("brick.bmp", "defaultBrick"))
        std::cout << "loadTexture('brick.bmp') Failed !\n";
    if(!assetManager_m->loadTexture("ball20.bmp", "defaultBall"))
        std::cout << "loadTexture('ball20.bmp') Failed !\n";
    if(!assetManager_m->loadTexture("wallV.bmp", "defaultWallV"))
        std::cout << "loadTexture('wallV.bmp') Failed !\n";
    if(!assetManager_m->loadTexture("wallH.bmp", "defaultWallH"))
        std::cout << "loadTexture('wallH.bmp') Failed !\n";
    std::cout << "[engine] EngineLite.default assets loaded!\n";
    
    levelFactory_m = new LevelFactory(assetManager_m);
    if (levelFactory_m == nullptr) {
        std::cout << "[engine] Failed on new LevelFactory(...) !\n";
        return;
    }
    //levelFactory_m->addNewLevelTemplate("level01.xml", "1");
    levelFactory_m->addNewLevelTemplate("level02.xml", "2");
    levelFactory_m->addNewLevelTemplate("level03.xml", "3");
    levelFactory_m->addNewLevelTemplate("level04.xml", "4");
    levelFactory_m->addNewLevelTemplate("level05.xml", "5");
    
    SDL_Point levelPos;
    levelPos.x = windowW * 0.25f;
    levelPos.y = 0;
    
    Level* pLevel = nullptr;
    pLevel = levelFactory_m->spawnLevelFromTemplate("5", levelPos, windowW, windowH);
    if (pLevel != nullptr) 
        levels_m.push_back(pLevel);
    pLevel = levelFactory_m->spawnLevelFromTemplate("3", levelPos, windowW, windowH);
    if (pLevel != nullptr) 
        levels_m.push_back(pLevel);
    //pLevel = levelFactory_m->spawnLevelFromTemplate("4", levelPos, windowW, windowH);
    //if (pLevel != nullptr) 
        //levels_m.push_back(pLevel);        
    //pLevel = levelFactory_m->spawnLevelFromTemplate("2", levelPos, windowW, windowH);
    //if (pLevel != nullptr) 
        //levels_m.push_back(pLevel);

    guiLevelName_m = new Text(renderer_m, assetManager_m->getFont(), SDL_Point{10, 230});
    if (guiLevelName_m == nullptr) {
        std::cout << "[engine] Failed on new Text(...) !\n";
        return;
    }
    getNextLevel();
}

EngineLite::~EngineLite() {
    currentLevel_m = nullptr;
    for (auto& l : levels_m) delete l;
    delete guiLevelName_m;
    delete levelFactory_m;
    delete assetManager_m;
    
    SDL_DestroyRenderer(renderer_m);
    SDL_DestroyWindow(window_m);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void EngineLite::handleEvents() {
    SDL_Event event;
    while ( SDL_PollEvent(&event) ) {
        if(event.type == SDL_QUIT) running_m = false;
        if (currentLevel_m == nullptr) return;
        if(event.type == SDL_KEYDOWN)
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_a: currentLevel_m->player()->velocity(SDL_FPoint{-1,  0}); break;
                case SDLK_RIGHT:
                case SDLK_d: currentLevel_m->player()->velocity(SDL_FPoint{ 1,  0}); break;
                case SDLK_p: currentLevel_m->pause(); break;
        }
        if(event.type == SDL_KEYUP)
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_a:
                case SDLK_RIGHT:
                case SDLK_d: currentLevel_m->player()->velocity(SDL_FPoint{ 0, 0}); break;
        }
    }
}
void EngineLite::update(float deltaTime) {
    if (currentLevel_m == nullptr) return;
    else if (currentLevel_m->victory()) {
        SDL_Delay(1000);
        getNextLevel();
    }
    else currentLevel_m->update();
}
void EngineLite::render() {
    SDL_SetRenderDrawColor(renderer_m, 50, 50, 99, 255);
    SDL_RenderClear(renderer_m);

    if (currentLevel_m == nullptr || guiLevelName_m == nullptr) return;
    currentLevel_m->render();
    guiLevelName_m->render();
    
    SDL_RenderPresent(renderer_m);
}
void EngineLite::getNextLevel() {
    for (int i = 0; i<levels_m.size(); i++)
        if ( !levels_m.at(i)->levelOver() ) {
            currentLevel_m = levels_m.at(i);
            std::string levelName = "Level " + std::to_string(i+1) + "/" +
                                    std::to_string(levels_m.size());
            std::cout << "levelName = " << levelName << "!\n";
            guiLevelName_m->text(levelName);
            return;
        }
}
bool EngineLite::running() const {return running_m;}

