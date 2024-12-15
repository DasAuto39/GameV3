#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>

#include "SaveLoad.h"
#include "RenderWindow.h"
#include "Entity.h"
#include "Map.h"
#include "MyCharacter.h"
#include "Ballz.h"
#include "ballmovement.h"

void resetGame(MyCharacter& Mine, Entity Crates[], ballmovement ballLtoR[], ballmovement ballRtoL[], SDL_Texture* MC, SDL_Texture* ball, SDL_Texture* crates) {
    Mine = MyCharacter(350, 500, MC);  // Reset player position and state
    //    Mine.setLife(5);

        // Reset ball positions
    ballLtoR[0] = ballmovement(32, 100, ball);
    ballLtoR[1] = ballmovement(32, 300, ball);
    ballLtoR[2] = ballmovement(32, 500, ball);
    ballRtoL[0] = ballmovement(604, 160, ball);
    ballRtoL[1] = ballmovement(604, 310, ball);
    ballRtoL[2] = ballmovement(604, 510, ball);

    // Generate possible positions for crates
    std::vector<SDL_Rect> positions[8];
    for (int x = 0; x < 580; x += 50) {
        for (int y = 0; y < 600; y += 50) {
            if (y < 150) {
                positions[0].push_back({ x, y, 50, 50 });
                positions[1].push_back({ x, y, 50, 50 });
            }
            else if (y >= 150 && y < 300) {
                positions[2].push_back({ x, y, 50, 50 });
                positions[3].push_back({ x, y, 50, 50 });
            }
            else if (y >= 300 && y < 450) {
                positions[4].push_back({ x, y, 50, 50 });
                positions[5].push_back({ x, y, 50, 50 });
            }
            else if (y >= 450 && y < 500) {
                positions[6].push_back({ x, y, 50, 50 });
            }
            else if (y >= 500 && y < 550) {
                positions[7].push_back({ x, y, 50, 50 });
            }
        }
    }

    // Shuffle the positions
    for (int i = 0; i < 8; ++i) {
        std::random_shuffle(positions[i].begin(), positions[i].end());
    }

    // Assign positions to crates
    for (int i = 0; i < 8; ++i) {
        Crates[i] = Entity(positions[i][0].x, positions[i][0].y, crates);
    }
}

// Function to randomly spawn the flask
void spawnFlask(Entity& flaskEntity, SDL_Texture* flaskTexture) {
    int x = rand() % 650; // Random x position within window width
    int y = rand() % 600; // Random y position within window height
    flaskEntity = Entity(x, y, flaskTexture);
}

int main(int argc, char** argv) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    srand(static_cast<unsigned int>(time(0))); // Initialize random seed

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    Mix_Chunk* soundMati = Mix_LoadWAV("sound/downer_noise.wav");
    if (soundMati == nullptr) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    Mix_Chunk* soundGelas = Mix_LoadWAV("sound/glass.wav");
    if (soundGelas== nullptr) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }
    
    Mix_Music* menumusic = Mix_LoadMUS("sound/menu_music.mp3");
    if (menumusic == nullptr) {
        std::cerr << "Failed to load MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    Mix_Music* ingamemusic = Mix_LoadMUS("sound/ingamemusic.mp3");
    if (ingamemusic == nullptr) {
        std::cerr << "Failed to load MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "TTF_Init has failed. Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cerr << "SDL_Init has failed. SDL_ERROR: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cerr << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    

    RenderWindow window("GAME v1.0", 700, 640);
    Map gameMap(&window);

    // Load assets
    SDL_Texture* Batu = window.loadTexture("img_obj/1.png");
    SDL_Texture* crates = window.loadTexture("img_obj/crate.png");
    SDL_Texture* MC = window.loadTexture("img_obj/elf_f_idle_anim_f0.png");
    SDL_Texture* ball = window.loadTexture("img_obj/tile000.png");
    SDL_Texture* flask = window.loadTexture("img_obj/flask_big_blue.png");
    TTF_Font* font16 = TTF_OpenFont("fonts/cocogoose.ttf", 16);
    SDL_Color white = { 255, 255, 255 };

    // Initialize ball movements
    ballmovement ballLtoR[3] =
    {
        ballmovement(32, 100, ball),
        ballmovement(32, 300, ball),
        ballmovement(32, 500, ball)
    };
    ballmovement ballRtoL[3] =
    {
        ballmovement(604, 160, ball),
        ballmovement(604, 300, ball),
        ballmovement(604, 500, ball)
    };

    // Initialize entities
    Entity entities[6] =
    {
        Entity(-32, 100, Batu),
        Entity(636, 160, Batu),
        Entity(-32, 300, Batu),
        Entity(636, 310, Batu),
        Entity(-32, 500, Batu),
        Entity(636, 510, Batu)
    };

    Entity Crates[8] =
    {
        Entity(250, 54, crates),
        Entity(344, 54, crates),
        Entity(54, 152, crates),
        Entity(598, 152, crates),
        Entity(152, 250, crates),
        Entity(500, 250, crates),
        Entity(250, 442, crates),
        Entity(344, 442, crates)
    };

    MyCharacter Mine(250, 300, MC);
    bool gameRunning = true;
    bool gameOver = false;
    bool inMainMenu = true;
    bool gamePause = false;
    SDL_Event event;

    // Flask related variables
    Entity flaskEntity(0, 0, flask);
    bool flaskActive = true;
    spawnFlask(flaskEntity, flask); // Initial spawn

while (gameRunning) {
    frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameRunning = false;
        }
        if (inMainMenu) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                inMainMenu = false; // Start the game
                Mix_HaltMusic(); // Stop menu music
                if (Mix_PlayMusic(ingamemusic, -1) == -1) { // Loop indefinitely
                    std::cerr << "Failed to play in-game MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
                }
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_l) {
                // Load game state
                if (!loadGame(Mine, Crates, MC, crates)) {
                    std::cerr << "Failed to load the game!" << std::endl;
                } else {
                    inMainMenu = false; // Start the game if load is successful
                    Mix_HaltMusic(); // Stop menu music
                    if (Mix_PlayMusic(ingamemusic, -1) == -1) { // Loop indefinitely
                        std::cerr << "Failed to play in-game MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    }
                }
            }
        } else {
            if (!gameOver) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {
                    gamePause = true;
                    Mix_HaltMusic(); // Stop the in-game music
                    if (Mix_PlayMusic(menumusic, -1) == -1) { // Play pause menu music
                        std::cerr << "Failed to play menu MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    }
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_e) {
                    // Save game state before exiting
                    saveGame(Mine, Crates);
                    gameRunning = false;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c) {
                    gamePause = false;
                    Mix_HaltMusic(); // Stop pause music
                    if (Mix_PlayMusic(ingamemusic, -1) == -1) { // Resume in-game music
                        std::cerr << "Failed to play in-game MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
                    }
                }
                if (!gamePause) {
                    Mine.handleEvent(event); // Only handle events when not paused
                }
            } else {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        // Restart the game
                        resetGame(Mine, Crates, ballLtoR, ballRtoL, MC, ball, crates);
                        gameOver = false;
                        Mix_HaltMusic(); // Stop game over music
                        if (Mix_PlayMusic(ingamemusic, -1) == -1) { // Resume in-game music
                            std::cerr << "Failed to play in-game MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
                        }
                    } else if (event.key.keysym.sym == SDLK_q) {
                        gameRunning = false; // End the game
                    }
                }
            }
        }
    }

    // Play menu music in the main menu
    if (inMainMenu && !Mix_PlayingMusic()) {
        if (Mix_PlayMusic(menumusic, -1) == -1) { // Loop indefinitely
            std::cerr << "Failed to play MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
    }

    // Play pause music
    if (gamePause && !Mix_PlayingMusic()) {
        if (Mix_PlayMusic(menumusic, -1) == -1) { // Loop indefinitely
            std::cerr << "Failed to play MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
    }

    // Play game over music
    if (gameOver && !Mix_PlayingMusic()) {
        if (Mix_PlayMusic(menumusic, -1) == -1) { // Loop indefinitely
            std::cerr << "Failed to play MP3! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
    }

    if (flaskActive && Mine.checkCollisionWithFlask(flaskEntity)) {
        flaskActive = false;
        Mine.addPoint();
        Mix_PlayChannel(-1, soundGelas, 0);
        spawnFlask(flaskEntity, flask); // Spawn a new flask
        flaskActive = true;
    }

    window.clear();

    if (inMainMenu) {
        // Render main menu
        window.render(250, 300, "Press SPACE to Play", font16, white);
        window.render(250, 350, "Press L to Load Game", font16, white);
    } else {
        if (!gameOver) {
            if (!gamePause) {
                // Update game logic
                Mine.update(Crates, 8);
                Mine.checkCollisionWithBalls(ballLtoR, 3);
                Mine.checkCollisionWithBalls(ballRtoL, 3);
 
                for (int i = 0; i < 3; i++) {
                    ballLtoR[i].update(Crates, Mine, 8, 10);
                    ballRtoL[i].update(Crates, Mine, 8, 10);


                }
            }

            if (Mine.getlife() == 0) {
                gameOver = true;
                Mix_HaltMusic(); // Stop the in-game music
                Mix_PlayChannel(-1, soundMati, 0);
            }

            gameMap.cldrawmap();

            // Render game entities
            for (int i = 0; i < 6; i++) {
                window.render(entities[i]);
            }
            for (int i = 0; i < 8; i++) {
                window.render(Crates[i]);
            }
            for (int i = 0; i < 3; i++) {
                window.render(ballLtoR[i]);
                window.render(ballRtoL[i]);
            }

            window.render(Mine);
            window.renderStats(Mine, 0, 0, font16, white);
            window.render(0, 40, "Press P to Pause", font16, white);
            window.render(0, 60, "Press E to Save & Exit", font16, white);

            if (gamePause) {
                window.render(250, 200, "Game Paused", font16, white);
                window.render(250, 250, "Press C to Continue", font16, white);
                window.render(250, 300, "Press E to Save & Exit", font16, white);
            }

            if (flaskActive) {
                window.render(flaskEntity);
            }
        } else {
            // Render game over screen
            window.render(250, 200, "Game Over", font16, white);
            window.render(250, 300, "Press ENTER to Restart", font16, white);
            window.render(250, 350, "Press Q to Quit", font16, white);
        }
    }

    window.display();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
        SDL_Delay(frameDelay - frameTime);
    }
}


    window.cleanUp();
    TTF_CloseFont(font16);
    Mix_FreeChunk(soundMati);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}