#include "Ballz.h"

Ballz::Ballz(float p_x, float p_y, SDL_Texture* p_tex)
    : xposB(p_x), yposB(p_y), texB(p_tex), xspeedB(2), yspeedB(1) {
    currentFrameB.x = 0;
    currentFrameB.y = 0;
    currentFrameB.w = 32;
    currentFrameB.h = 32;
}

SDL_Rect* Ballz::rtunSRCB() {
    srcB.x = currentFrameB.x;
    srcB.y = currentFrameB.y;
    srcB.w = currentFrameB.w;
    srcB.h = currentFrameB.h;

    return &srcB;
}

SDL_Rect* Ballz::rtunDSTB() {
    dstB.x = xposB;
    dstB.y = yposB;
    dstB.w = currentFrameB.w * 2;
    dstB.h = currentFrameB.h * 2;

    return &dstB;
}

float Ballz::GetXposB() const {
    return xposB;
}

float Ballz::GetYposB() const {
    return yposB;
}

SDL_Rect Ballz::GetNotptrDSTB()
{
    return dstB;
}

SDL_Texture* Ballz::getTexB() {
    return texB;
}

SDL_Rect Ballz::getCurrentFrameB() {
    return currentFrameB;
}
float Ballz::GetXspeedB()
{
    return xspeedB;
}
float Ballz::GetYspeedB()
{
    return yspeedB;
}