#include "Entity.h"


Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
	:xE(p_x), yE(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

float Entity::getXE()
{
	return xE;
}
float Entity::getYE()
{
	return yE;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect* Entity::rtunSRCE()
{
	srcE.x = currentFrame.x;
	srcE.y = currentFrame.y;
	srcE.w = currentFrame.w;
	srcE.h = currentFrame.h;

	return &srcE;
}

SDL_Rect* Entity::rtunDSTE()
{
	dstE.x = xE;
	dstE.y = yE;
	dstE.w = currentFrame.w * 2;
	dstE.h = currentFrame.h * 2;

	return &dstE;
}

SDL_Rect Entity::GetNotptrDSTE()
{
	return dstE;
}


SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::setPosition(float p_x, float p_y)
{
	currentFrame.x = p_x;
	currentFrame.y = p_y;
}

