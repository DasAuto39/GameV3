#include "SaveLoad.h"
#include <iostream>

void saveGame(MyCharacter& Mine, Entity Crates[]) {
    std::ofstream saveFile("savegame.txt");
    if (saveFile.is_open()) {
        // Save the player's position, life, and points
        saveFile << Mine.getxpos() << " " << Mine.getypos() << " "
            << Mine.getLife() << " " << Mine.getPoints() << "\n";

        // Save the crates' positions
        for (int i = 0; i < 8; i++) {
            saveFile << Crates[i].getXE() << " " << Crates[i].getYE() << "\n";
        }

        saveFile.close();
    }
    else {
        std::cerr << "Unable to open save file for writing!" << std::endl;
    }
}

bool loadGame(MyCharacter& Mine, Entity Crates[], SDL_Texture* MC, SDL_Texture* crates) {
    std::ifstream loadFile("savegame.txt");
    if (loadFile.is_open()) {
        float x, y;
        int life,points;
        

        // Load the player's position, life, and points
        loadFile >> x >> y >> life >> points;
        Mine = MyCharacter(x, y, MC);
        Mine.setLife(life);
        Mine.setPoint(points);

        // Load the crates' positions
        for (int i = 0; i < 8; i++) {
            loadFile >> x >> y;
            Crates[i] = Entity(x, y, crates);
        }

        loadFile.close();
        return true;
    }
    else {
        std::cerr << "Unable to open save file for reading!" << std::endl;
        return false;
    }
}
