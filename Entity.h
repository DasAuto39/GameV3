#ifndef ENTITY_H
#define ENTITY_H


#include "SDL.h"
#include "SDL_image.h"
class Entity {
public:
	Entity(float p_x, float p_y, SDL_Texture* p_tex);
	float getXE();
	float getYE();
	SDL_Rect* rtunSRCE();
	SDL_Rect* rtunDSTE();
	SDL_Rect GetNotptrDSTE();
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
	void setPosition(float x, float y);
	const SDL_Point getposition();
private:
	float xE, yE;
	SDL_Rect srcE, dstE;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
#endif ENTITY_H