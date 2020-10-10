#include "EngineLite.hpp"

int main() {

    EngineLite engine;

    const int FPS = 60, frameIdealDuration = 1000 / FPS;

    int frameEnd = 0.0;
    int deltaTime = 0.0;

    while(engine.running()) {
        int now = SDL_GetTicks();
        deltaTime = now - frameEnd;
        frameEnd = now;

        engine.handleEvents();
        engine.update(deltaTime/1000.0);
        engine.render();

        int frameDuration = SDL_GetTicks() - now;
        if (frameDuration < frameIdealDuration ) SDL_Delay(frameIdealDuration - frameDuration);
    }

    return 0;
}
