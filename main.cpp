#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
//#include <SDL2/SDL_ttf.h>
#include "engine.h"
#include "objects.h"
#include "defs.h"
#include "mechanics.h"
#include "stars.h"
#include "draw.h"

//Configuration Provider
//ms-vscode.makefile-tools

//ToDo

//Fix string to int issues with score
//Drawing objects upside-down
//Window engine

void GameLoop();
void InitNewGame();
void MenuLoop();

spacegame Game;

spaceplayer Player;

spaceobject Star[NUMSTARS];
spaceobject Ship;
//spaceobject Enemy[MAXNUMENEMIES];
//spaceobject HealthAmmo[MAXNUMHEALTHAMMO];
//spaceobject Laser[MAXNUMLASERS];
//spaceobject Explosion[MAXNUMEXPLOSIONS];

//const int frameDelay = 1000/10;
//const float frameDelay = 1000/60;
Uint32 frameStart;
Uint32 frameTime;
Uint32 frames = 0;
Uint32 startFrame;
Uint32 endFrame;

//int main(int argc, const char * argv[])
int main(int argv, char** args)
{
    std::cout << "\n\nStarting...\n\n";
    std::cout << "Space Battle!\n";
    std::cout << "Version 0.1.1\n";
    std::cout << "By Alex Crane\n\n";
    
    //Randomize Timer
    srand (static_cast <unsigned> (time_t(0)));

    Game.init("Space Battle!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    InitStars();

    //Player.highScore = Game.readHighScore();

    startFrame = SDL_GetTicks();

    Game.isPlaying = true;
    Player.inMenu = true;
    Player.inGame = false;

    Game.setKeysOff();

    LoadGraphics();

    GameLoop();

    //Quitting Starts Here

    endFrame = SDL_GetTicks();
    Uint32 totalTime = endFrame - startFrame;
    // std::cout << "Frames per second: " << frames / totalTime << std::endl;
    // std::cout << frames << std::endl;
    std::cout << "Total Time: " << totalTime << std::endl;

    Game.clean();
    std::cout << "Exiting...." << std::endl;

    return 0;
}

void GameLoop()
{
    while(Game.isPlaying)
    {
        frameStart = SDL_GetTicks();
        
        //Window fuctions and User Inputs
        Game.handleEvents();
            
        //Game.update();

        ProcessInputs();

        HandleStars();

        if(Player.inGame)
        {
            HandlePlayerShip();

            //TEMPORARY
            Game.mainViewport.targetX = Ship.posX;
            Game.mainViewport.targetY = Ship.posY;

            Game.mainViewport.scale = (1/abs(Ship.velX)) + 4;

            // Game.mainViewport.focusX = Ship.posX;
            // Game.mainViewport.focusY = Ship.posY;

            Game.mainViewport.updateViewport();

            //Game.mainViewport.

            //HandleLasers();
            //HandleHealthAmmo();
            //HandleExplosions();

            //CheckEndOfGame();
            //CheckEnemyNumbers();
        }

        if(Player.inMenu) MenuLoop();

        Game.renderClear();
        Draw();
        Game.renderPresent();

        //limit to 60 frameas per sec...for now
        frames++;
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){SDL_Delay(frameDelay - frameTime);}else{std::cout << "Frames Lost" << std::endl;}
    }

    Player.inMenu = true;
    std::cout << "Score: " << Player.score << std::endl;

    //CheckHighScore();
    
}

void MenuLoop()
{
    if(Game.usrKeyN)
    {
        Game.usrKeyN=false;
        Player.inGame = true;
        Player.inMenu = false;
        InitNewGame();
        //InitEnemies();
        //Game.playSound(3);
    }

    if(Game.usrKeyX)
    {
        Game.isPlaying = false;
        Game.usrKeyX = false;
    }
}

void InitNewGame()
{
    std::cout << "New Game Started" << std::endl;    

    Game.viewScale = 2;

    Ship.velX = 0;
    Ship.velY = 0;
    Ship.velA = 0;
    Ship.impFB = 0;
    Ship.impLR = 0;
    Ship.impA = 0;
    Ship.posX = SHIP_START_X;
    Ship.posY = SHIP_START_Y
    Ship.impFlevel = SHIP_IMPULSE_F;
    Ship.impBlevel = SHIP_IMPULSE_B;
    Ship.impAlevel = SHIP_IMPULSE_A;
    Ship.impLlevel = SHIP_IMPULSE_L;
    Ship.impRlevel = SHIP_IMPULSE_R;
    Ship.decA = SHIP_TURN_DECAY;
    Ship.decXY = SHIP_VEL_DECAY;
    Ship.maxVel = SHIP_MAX_VEL;
    Ship.maxTurnVel = SHIP_MAX_TURN_VEL;

    Game.mainViewport.scale = 1;
    Game.mainViewport.windowHeight = MAIN_VIEWPORT_HEIGHT;
    Game.mainViewport.windowWidth = MAIN_VIEWPORT_WIDTH;
    Game.mainViewport.windowX = MAIN_VIEWPORT_X;
    Game.mainViewport.windowY = MAIN_VIEWPORT_Y;
    Game.mainViewport.padding = VIEWPORT_PADDING;
    Game.mainViewport.shiftSpeed = VIEWPORT_SHIFT_SPEED;

    // Game.dataViewport.scale = 1;
    // Game.dataViewport.windowX = 400;
    // Game.dataViewport.windowY = 5;
    // Game.dataViewport.windowHeight = 745;
    // Game.dataViewport.windowWidth = 20;

    // Game.dataViewport.padding = 2;
    // Game.dataViewport.shiftSpeed = 2;

    Game.dataViewport.scale = 1;
    Game.dataViewport.windowHeight = DATA_VIEWPORT_HEIGHT;
    Game.dataViewport.windowWidth = DATA_VIEWPORT_WIDTH;
    Game.dataViewport.windowX = DATA_VIEWPORT_X;
    Game.dataViewport.windowY = DATA_VIEWPORT_Y;
    Game.dataViewport.padding = VIEWPORT_PADDING;
    Game.dataViewport.shiftSpeed = VIEWPORT_SHIFT_SPEED;

    // Game.testvp.scale = 1;
    // Game.testvp.windowHeight = 20;
    // Game.testvp.windowWidth = 20;
    // Game.testvp.windowX = 20;
    // Game.testvp.windowY = 20;
    // Game.testvp.padding = 2;
    // Game.testvp.shiftSpeed = 2;

    //Player.health = 100;
    //Player.score = 0;
    //Player.ammo = 100;

    //Player.numEnemyShips = 10;
    //Player.numEnemyShips = 400;
    
    //Player.shipToAdd = 15;
    //Player.stillPlaying = true;
    //Player.fireLaser = false;
    //Player.endOfGameStage = 0;

    // for(int i=0; i < MAXNUMEXPLOSIONS; i++)
    // {
    //     Explosion[i].active = false;
    // }

    // for(int i=0; i < MAXNUMLASERS; i++)
    // {
    //     Laser[i].active = false;
    // }

    // for(int i=0; i < MAXNUMHEALTHAMMO; i++)
    // {
    //     HealthAmmo[i].active = false;
    // }

    Game.setKeysOff();

}