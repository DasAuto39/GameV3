#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Entity.h"
#include "MyCharacter.h"
#include "Ballz.h"


class MyCharacter;

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void render(Entity& p_entity);
    void render(MyCharacter& p_MC);
    void render(Ballz& p_ball);
    void render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst);
    void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void renderStats(MyCharacter& character, float x, float y, TTF_Font* font, SDL_Color textColor);





    void display();
    void cleanUp();
    void clear();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
#endif // RENDERWINDOW_H