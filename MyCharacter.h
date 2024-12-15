    #ifndef MYCHARACTER_H
    #define MYCHARACTER_H

    #include "SDL.h"
    #include "SDL_image.h"
    #include "Entity.h"
    #include "Collision.h"
    #include <string>
    #include <algorithm>
    #include <iostream>
    class ballmovement; // Forward declaration
    class Ballz; // Forward declaration

    class MyCharacter : public Entity
    {
    private:
        Uint32 gracePeriodStart;
        static const Uint32 gracePeriodDuration = 1000; // 3 seconds
        SDL_Rect srcMC, dstMC;
        float xposMC, yposMC;
        int lifeMC = 5;
        int pointMC = 0;
        int xspeedMC, yspeedMC;
        SDL_Rect currentFrame;
        SDL_Texture* tex;


    public:
        MyCharacter(float p_x, float p_y, SDL_Texture* p_tex);
        void handleEvent(SDL_Event& event);
        void update(Entity crates[], int numCrates);
        void checkCollisionCrateAndMC(Entity crates[], int numCrates);
        void checkCollisionWithBalls(ballmovement ball[], int numBall);
        bool checkCollisionWithFlask(Entity& flask);
        void respawn();
        SDL_Texture* getTex();
        SDL_Rect* rtunSRCMC();
        SDL_Rect* rtunDSTMC();
        SDL_Rect getCurrentFrame();
        float getxpos();
        float getypos();
        int getlife();
        std::string getPoints() ;
        std::string getLife();
        void setLife(int rlife);
        void setPoint(int rpoint);
        void addPoint();



    };
    #endif // MYCHARACTER_H