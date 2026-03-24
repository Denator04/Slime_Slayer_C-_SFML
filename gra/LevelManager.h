#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <vector>
#include "Block.h"
#include "Coin.h"

class LevelManager {
public:
    bool levelCompleted = false; //Flaga ukoñczenia poziomu
    sf::Clock completionTimer;   // Zegar do odmierzania czasu po ukoñczeniu poziomu
    float completionDelay = 3.0f; // Czas trwania ekranu ukoñczenia (w sekundach)


    static void loadLevel1(std::vector<Block>& blocks, Coin& coinManager, sf::Texture& dirtTexture, sf::Texture& grassTexture, sf::Texture& woodTexture);
private:
    sf::RectangleShape Meta;
};

#endif