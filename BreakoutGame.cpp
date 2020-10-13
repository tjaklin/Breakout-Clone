#include "BreakoutGame.h"

BreakoutGame::BreakoutGame()
	: running_m{ true }, assetManager_m{ nullptr },
	levelFactory_m{ nullptr }, currentLevel_m{ nullptr },
	guiLevelName_m{ nullptr }, window_m{ nullptr },
	renderer_m{ nullptr }
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "[BreakoutGame] Failed on SDL_Init() !\n";
		throw std::runtime_error{ "SDL_Init()" };
	}
	if (TTF_Init() != 0) {
		std::cout << "[BreakoutGame] Failed on TTF_Init() !\n";
		throw std::runtime_error{ "TTF_Init()" };
	}

	const int windowW = 1024;
	const int windowH = 768;

	window_m = SDL_CreateWindow("BreakoutGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowW, windowH, SDL_WINDOW_SHOWN);
	if (window_m == nullptr) {
		std::cout << "[BreakoutGame] Failed on SDL_CreateWindow() !\n";
		throw std::runtime_error{ "SDL_CreateWindow()" };
	}
	renderer_m = SDL_CreateRenderer(window_m, -1, SDL_RENDERER_ACCELERATED);
	if (renderer_m == nullptr) {
		std::cout << "[BreakoutGame] Failed on SDL_CreateRenderer() !\n";
		throw std::runtime_error{ "SDL_CreateRenderer()" };
	}
	assetManager_m = new AssetManager(renderer_m);
	if (assetManager_m == nullptr) {
		std::cout << "[BreakoutGame] Failed on new AssetManager(...) !\n";
		throw std::runtime_error{ "AssetManager(...)" };
	}
	int fontSize = static_cast<int>(0.025f * windowW);
	assetManager_m->loadFont("Fonts/myFont.ttf", fontSize);
	assetManager_m->loadTexture("Textures/Boards/background.bmp", "defaultBackground");
	assetManager_m->loadTexture("Textures/Objects/player80.bmp", "defaultPlayer");
	assetManager_m->loadTexture("Textures/Objects/brick.bmp", "defaultBrick");
	assetManager_m->loadTexture("Textures/Objects/ball20.png", "defaultBall");
	assetManager_m->loadTexture("Textures/Objects/wallV.bmp", "defaultWallV");
	assetManager_m->loadTexture("Textures/Objects/wallH.bmp", "defaultWallH");

	levelFactory_m = new LevelFactory(assetManager_m);
	if (levelFactory_m == nullptr) {
		std::cout << "[BreakoutGame] Failed on new LevelFactory(...) !\n";
		throw std::runtime_error{ "LevelFactory(...)" };
	}
	levelFactory_m->addNewLevelTemplate("Levels/level02.xml", "2");
	levelFactory_m->addNewLevelTemplate("Levels/level03.xml", "3");
	levelFactory_m->addNewLevelTemplate("Levels/level04.xml", "4");
	levelFactory_m->addNewLevelTemplate("Levels/level05.xml", "5");
	levelFactory_m->addNewLevelTemplate("Levels/level06.xml", "6");

	SDL_Point levelPos;
	levelPos.x = static_cast<int>(windowW * 0.25);
	levelPos.y = 0;

	Level* pLevel = nullptr;
	pLevel = levelFactory_m->spawnLevelFromTemplate("6", levelPos, windowW, windowH);
	if (pLevel != nullptr)
		levels_m.push_back(pLevel);
	pLevel = levelFactory_m->spawnLevelFromTemplate("5", levelPos, windowW, windowH);
	if (pLevel != nullptr)
		levels_m.push_back(pLevel);
	pLevel = levelFactory_m->spawnLevelFromTemplate("3", levelPos, windowW, windowH);
	if (pLevel != nullptr)
		levels_m.push_back(pLevel);
	pLevel = levelFactory_m->spawnLevelFromTemplate("4", levelPos, windowW, windowH);
	if (pLevel != nullptr) 
		levels_m.push_back(pLevel);        
	pLevel = levelFactory_m->spawnLevelFromTemplate("2", levelPos, windowW, windowH);
	if (pLevel != nullptr) 
		levels_m.push_back(pLevel);

	guiLevelName_m = new Text(renderer_m, assetManager_m->getFont(), SDL_Point{ 10, 230 });
	if (guiLevelName_m == nullptr) {
		std::cout << "[BreakoutGame] Failed on new Text(...) !\n";
		throw std::runtime_error{ "Text(...)" };
	}
	getNextLevel();
}

BreakoutGame::~BreakoutGame() {
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

void BreakoutGame::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) running_m = false;
		if (currentLevel_m == nullptr) return;
		if (event.type == SDL_KEYDOWN)
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_a: currentLevel_m->player()->velocity(SDL_FPoint{ -1,  0 }); break;
			case SDLK_RIGHT:
			case SDLK_d: currentLevel_m->player()->velocity(SDL_FPoint{ 1,  0 }); break;
			case SDLK_p: currentLevel_m->pause(); break;
			}
		if (event.type == SDL_KEYUP)
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_a:
			case SDLK_RIGHT:
			case SDLK_d: currentLevel_m->player()->velocity(SDL_FPoint{ 0, 0 }); break;
			}
	}
}
void BreakoutGame::update() {
	if (currentLevel_m == nullptr) return;
	else if (currentLevel_m->victory()) {
		// Prièekaj 1s da se igraè pripremi.
		SDL_Delay(1000);
		getNextLevel();
	}
	else currentLevel_m->update();
}
void BreakoutGame::render() {
	SDL_SetRenderDrawColor(renderer_m, 50, 50, 99, 255);
	SDL_RenderClear(renderer_m);

	if (currentLevel_m == nullptr || guiLevelName_m == nullptr) return;
	currentLevel_m->render();
	guiLevelName_m->render();

	SDL_RenderPresent(renderer_m);
}
void BreakoutGame::getNextLevel() {
	for (int i = 0; i < levels_m.size(); i++)
		if (!levels_m.at(i)->levelOver()) {
			currentLevel_m = levels_m.at(i);
			std::string levelName = "Level " + std::to_string(i + 1) + "/" +
				std::to_string(levels_m.size());
			guiLevelName_m->text(levelName);
			return;
		}
}
bool BreakoutGame::running() const { return running_m; }