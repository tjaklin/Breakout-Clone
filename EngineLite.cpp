#include "EngineLite.hpp"

EngineLite::EngineLite()
   : running_m{true}, assetManager_m{nullptr}, levelFactory_m{nullptr}, currentLevel_m{nullptr}
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    
    const int windowW = 1024;
    const int windowH = 768;
    window_m = SDL_CreateWindow("EngineLite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                windowW, windowH, SDL_WINDOW_SHOWN);
    renderer_m = SDL_CreateRenderer(window_m, -1, SDL_RENDERER_ACCELERATED);
    
    std::cout << "[engine] EngineLite!\n";
    assetManager_m = new AssetManager(renderer_m);
    if (assetManager_m == nullptr) std::cout << "assetManager_m == nullptr!\n";
    else std::cout << "[engine] EngineLite.assetManager_m created!\n";
    if (!assetManager_m->loadFont("./myFont.ttf", 24)) std::cout << "loadFont() Failed !\n";
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
    //levelFactory_m->addNewLevelTemplate("level01.xml", "1");
    levelFactory_m->addNewLevelTemplateTest("level02.xml", "2");
    
    // TODO: Ubaciti Text da se rendera tu, umjesto u Level-u !
    SDL_Point levelPos;
    levelPos.x = windowW * 0.25f;
    levelPos.y = 0;
    
    currentLevel_m = levelFactory_m->spawnLevelFromTemplate("2", levelPos, windowW, windowH);
    
    std::cout << "[engine] EngineLite.LevelCreated!\n";
}

EngineLite::~EngineLite() {
    currentLevel_m = nullptr;
    for (auto& l : levels_m) delete l;
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
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) running_m = false;
    if(event.type == SDL_KEYDOWN)
        switch (event.key.keysym.sym) {
            case SDLK_a: currentLevel_m->player()->velocity(SDL_FPoint{-1,  0}); break;
            case SDLK_d: currentLevel_m->player()->velocity(SDL_FPoint{ 1,  0}); break;
//             case SDLK_w: currentLevel_m->player()->velocity(SDL_FPoint{ 0, -1}); break;
//             case SDLK_s: currentLevel_m->player()->velocity(SDL_FPoint{ 0,  1}); break;
            case SDLK_p: currentLevel_m->pause(); break;
    }
    if(event.type == SDL_KEYUP)
        switch (event.key.keysym.sym) {
            case SDLK_a:
            case SDLK_d: currentLevel_m->player()->velocity(SDL_FPoint{ 0, 0}); break;
//             case SDLK_w:
//             case SDLK_s:
    }
}
void EngineLite::update(float deltaTime) {currentLevel_m->update();}
void EngineLite::render() {
    SDL_SetRenderDrawColor(renderer_m, 0, 127, 127, 255);
    SDL_RenderClear(renderer_m);

    currentLevel_m->render();

    SDL_RenderPresent(renderer_m);
}
