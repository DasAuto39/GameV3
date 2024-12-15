#ifndef BALLZ_H
#define BALLZ_H
#include "SDL.h"
#include "SDL_image.h"

class Ballz {
public:
    Ballz();
    Ballz(float p_x, float p_y, SDL_Texture* p_tex);
    SDL_Rect* rtunSRCB();
    SDL_Rect* rtunDSTB();
    SDL_Texture* getTexB();
    float GetXposB() const;
    float GetYposB() const;
    float GetXspeedB();
    float GetYspeedB();
    SDL_Rect GetNotptrDSTB();
    SDL_Rect getCurrentFrameB();
protected:
    float xposB, yposB;
    int xspeedB, yspeedB;
    

private:
    SDL_Rect srcB, dstB;
    SDL_Rect currentFrameB;
    SDL_Texture* texB;
};

#endif // BALLZ_H