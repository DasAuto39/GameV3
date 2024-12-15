#include "ballmovement.h"
#include "Collision.h"
#include <algorithm>

ballmovement::ballmovement(float p_x, float p_y, SDL_Texture* p_tex)
    : Ballz(p_x, p_y, p_tex), wanderAngle(0.0f) {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random number generator
}

void ballmovement::update(Entity crates[], MyCharacter mine, int numCrates, float followRadius) {
    float playerX = mine.getypos();
    float playerY = mine.getxpos();

    float distance = distanceToPlayer(playerX, playerY);
    if (distance <= followRadius) {
        followPlayer(playerX, playerY);
    }
    else {
        wander(); // If player is out of range, switch to wandering
    }

    checkCollision(crates, numCrates);
}

SDL_Rect ballmovement::GetNotptrDSTBMB() {
    return Ballz::GetNotptrDSTB();
}

void ballmovement::followPlayer(float playerX, float playerY) {
    float dx = playerX - xposB;
    float dy = playerY - yposB;
    float distance = std::sqrt(dx * dx + dy * dy);
    float angle_radian = atan2(dy, dx);
    
    float xspeedball = Ballz::GetXspeedB() * cos(angle_radian);
    float yspeedball = Ballz::GetYspeedB() * sin(angle_radian);


    xposB += xspeedball;
    yposB += yspeedball;
    
}

void ballmovement::wander() {
    wanderAngle += (std::rand() % 21 - 10) * 0.1f; // Adjust angle randomly
    float radians = wanderAngle * M_PI / 180.0f;
    xposB += std::cos(radians) * xspeedB;
    yposB += std::sin(radians) * yspeedB;

    // Keep the ball within screen boundaries (example values)
    if (xposB < 0) {
        xposB = 0;
        wanderAngle = std::rand() % 360; // Change direction
    }
    else if (xposB > 720) {
        xposB = 720;
        wanderAngle = std::rand() % 360; // Change direction
    }

    if (yposB < 0) {
        yposB = 0;
        wanderAngle = std::rand() % 360; // Change direction
    }
    else if (yposB > 480) {
        yposB = 480;
        wanderAngle = std::rand() % 360; // Change direction
    }
}

float ballmovement::distanceToPlayer(float playerX, float playerY) {
    float dx = playerX - xposB;
    float dy = playerY - yposB;
    return std::sqrt(dx * dx + dy * dy);
}
void ballmovement::checkCollision(Entity crates[], int numCrates) {
    SDL_Rect ballRect = { static_cast<int>(xposB), static_cast<int>(yposB),
                          getCurrentFrameB().w * 2, getCurrentFrameB().h * 2 };

    for (int i = 0; i < numCrates; i++) {
        if (Collision::checkCollision(ballRect, crates[i].GetNotptrDSTE())) {
            // Calculate a new direction to avoid the crate
            adjustDirection(crates[i].GetNotptrDSTE());
            break;
        }
    }
}

void ballmovement::adjustDirection(const SDL_Rect& crateRect) {
    float crateCenterX = crateRect.x + crateRect.w / 2.0f;
    float crateCenterY = crateRect.y + crateRect.h / 2.0f;

    // Calculate direction away from the crate
    float dx = xposB - crateCenterX;
    float dy = yposB - crateCenterY;

    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance == 0.0f) distance = 1.0f; // Prevent division by zero

    // Normalize the direction vector and adjust the position
    dx /= distance;
    dy /= distance;

    xposB += dx * xspeedB; // Move away in the x-direction
    yposB += dy * yspeedB; // Move away in the y-direction

    // Randomly adjust the wander angle slightly to create a smoother avoidance
    wanderAngle += (std::rand() % 21 - 10) * 0.1f;
}
