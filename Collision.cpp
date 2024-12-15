#include "Collision.h"


bool Collision::checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    // Calculate the sides of rect A
    int leftA = a.x + 10;
    int rightA = (a.x + a.w) - 10;
    int topA = a.y + 30;
    int bottomA = (a.y + a.h) - 10;

    // Calculate the sides of rect B
    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }
    if (topA >= bottomB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}
