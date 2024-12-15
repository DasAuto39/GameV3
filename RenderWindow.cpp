#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	return texture;
}




void RenderWindow::render(Entity& p_entity)
{
	SDL_RenderCopy(renderer, p_entity.getTex(), p_entity.rtunSRCE(), p_entity.rtunDSTE());
}

void RenderWindow::render(MyCharacter& p_MC)
{
	SDL_RenderCopy(renderer, p_MC.getTex(), p_MC.rtunSRCMC(), p_MC.rtunDSTMC());
}

void RenderWindow::render(Ballz& p_ball)
{
	SDL_RenderCopy(renderer, p_ball.getTexB(), p_ball.rtunSRCB(), p_ball.rtunDSTB());
}

void RenderWindow::render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dst)  // Ensure this is defined
{
	SDL_RenderCopy(renderer, texture, &src, &dst);
}

void RenderWindow::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, p_text, textColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surfaceMessage->w;
	src.h = surfaceMessage->h;

	SDL_Rect dst;
	dst.x = p_x;
	dst.y = p_y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, message, &src, &dst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);  // Don't forget to destroy the texture to avoid memory leaks
}

void RenderWindow::renderStats(MyCharacter& character, float x, float y, TTF_Font* font, SDL_Color textColor)
{
	// Render lives
	std::string lifeText = "Lives: " + character.getLife();
	render(x, y, lifeText.c_str(), font, textColor);

	// Render points
	std::string pointsText = "Points: " + character.getPoints();
	render(x, y + 20, pointsText.c_str(), font, textColor); // Adjust y position for spacing
}






void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}


void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}