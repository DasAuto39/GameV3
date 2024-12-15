#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "MyCharacter.h"
#include "Entity.h"
#include <fstream>

void saveGame(MyCharacter& Mine, Entity Crates[]);
bool loadGame(MyCharacter& Mine, Entity Crates[], SDL_Texture* MC, SDL_Texture* crates);

#endif // SAVELOAD_H
