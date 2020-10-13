#include "BreakoutGame.h"

int main(int argc, char *args[]) {

	BreakoutGame* game = nullptr;
	try { game = new BreakoutGame(); }
	catch (std::runtime_error) {
		std::cout << "[main] Failed at new EngineLite() !\n";
		delete game;
		return -1;
	}

	const int FPS = 60, frameIdealDuration = 1000 / FPS;

	while (game->running()) {
		int frameBegin = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		int frameDuration = SDL_GetTicks() - frameBegin;
		if (frameDuration < frameIdealDuration) SDL_Delay(frameIdealDuration - frameDuration);
	}

	delete game;
	return 0;
}
