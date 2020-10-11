#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text {
public:
    Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Point pos,
         SDL_Color color = SDL_Color{255, 255, 255, 255});
    ~Text();
    
    void render();
    void text(std::string text);
private:
    SDL_Renderer* renderer_m;
    TTF_Font* font_m;
    SDL_Rect rect_m;
    SDL_Color color_m;
    SDL_Texture* texture_m;
};
#endif // TEXT_HPP
