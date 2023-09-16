//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Saucer.h"


void loadResources();
void populateWorld();


int main(int argc, char* argv[]) 
{

    // Start up game manager.
    df::GameManager& gameManager = df::GameManager::getInstance();
    if (gameManager.startUp()) 
    {
        df::LogManager& log_manager = df::LogManager::getInstance();
        log_manager.setFlush(true);
        log_manager.writeLog("Error starting game manager!");
        gameManager.shutDown();
        return 0;
    }

    df::splash();

    loadResources();
    populateWorld();
    gameManager.run();

    // Shut everything down.
    gameManager.shutDown();
}



void loadResources()
{
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
}


void populateWorld()
{
    new Saucer();
}