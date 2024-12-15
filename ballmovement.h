#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include "Ballz.h"
#include "SDL.h"
#include "Collision.h"
#include "Entity.h"
#include "MyCharacter.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

class ballmovement : public Ballz {
public:
    ballmovement(float p_x, float p_y, SDL_Texture* p_tex);
    void update(Entity crates[],MyCharacter mine, int numCrates,  float followRadius);
    SDL_Rect GetNotptrDSTBMB();
    void checkCollision(Entity crates[], int numCrates);
    void adjustDirection(const SDL_Rect& crateRect);

private:
    void followPlayer(float playerX, float playerY);
    void wander();
    float distanceToPlayer(float playerX, float playerY);

    float wanderAngle; // Used for wandering behavior
};

#endif // BALLMOVEMENT_H