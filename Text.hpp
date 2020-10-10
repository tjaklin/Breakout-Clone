#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text {
public:
    Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Point pos, std::string text, SDL_Color color = SDL_Color{255, 255, 255, 255});
    ~Text();
    
    void render(SDL_Renderer* renderer);
    void text(std::string text, SDL_Renderer* renderer, TTF_Font* font);
    
    const std::string text() const;
    const SDL_Color color() const;
    const SDL_Rect rect() const;    
private:
    std::string text_m;
    SDL_Color color_m;
    SDL_Rect rect_m;
    SDL_Texture* texture_m;
};

#endif // TEXT_HPP
