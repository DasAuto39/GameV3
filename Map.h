#ifndef MAP_H
#define MAP_H


#include "RenderWindow.h"
#include "SDL.h"
#include "SDL_image.h"

class Map
{
public:
    Map(RenderWindow* p_window);
    virtual ~Map();

    void clloadmap(int arr[20][25]);
    void cldrawmap();

private:
    SDL_Rect src, dst;
    RenderWindow* window;
    SDL_Texture* ground;
    SDL_Texture* wall;
    SDL_Texture* decoration;
    int map[20][25];
};

#endif // MAP_H