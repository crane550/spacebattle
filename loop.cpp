#include <SDL2/SDL.h>

#include "loop.h"
#include "engine.h"
#include "objects.h"
#include "defs.h"
#include "draw.h"
#include "mechanics.h"
#include "stars.h"
#include "util.h"

Uint32 frameStart;
Uint32 frameTime;

extern spacegame Game;
extern Uint32 frames;

spaceplayer Player;
spaceobject Star[NUMSTARS];
spaceobject Ship;
spaceobject Enemy[MAX_NUM_ENEMIES];


//spaceobject Enemy[MAXNUMENEMIES];
//spaceobject HealthAmmo[MAXNUMHEALTHAMMO];
//spaceobject Laser[MAXNUMLASERS];
//spaceobject Explosion[MAXNUMEXPLOSIONS];

void GameLoop()
{
    // Loading Screen here?
    
    Game.isPlaying = true;
    Player.inMenu = true;
    Player.inGame = false;
    Game.setKeysOff();
    InitStars();
    
    while(Game.isPlaying)
    {
        frameStart = SDL_GetTicks();
        
        //Window fuctions and User Inputs
        Game.handleEvents();

        // Use inputs to control Game
        ProcessInputs();

        HandleStars();

        if(Player.inGame)
        {
            
            HandlePlayerShip();

            UpdateViewport();

            // Enemy.posX = Ship.posX - 50;
            // Enemy.posY = Ship.posY - 50;
            // Enemy.posA = -Ship.posA + 90;

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

        // Limit to 60 frameas per second
        frames++;
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){SDL_Delay(frameDelay - frameTime);}else{std::cout << "Frames Lost" << std::endl;}
    }

    Player.inMenu = true;
    std::cout << "Game has ended" << std::endl;
    
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
    Ship.posA = 0;
    Ship.impFlevel = SHIP_IMPULSE_F;
    Ship.impBlevel = SHIP_IMPULSE_B;
    Ship.impAlevel = SHIP_IMPULSE_A;
    Ship.impLlevel = SHIP_IMPULSE_L;
    Ship.impRlevel = SHIP_IMPULSE_R;
    Ship.decA = SHIP_TURN_DECAY;
    Ship.decXY = SHIP_VEL_DECAY;
    Ship.maxVel = SHIP_MAX_VEL;
    Ship.maxTurnVel = SHIP_MAX_TURN_VEL;

    Ship.texture = Game.loadTexture("graphics/ship1.png");

    for(int i = 0; i < MAX_NUM_ENEMIES; i++)
    {
        Enemy[i].posX = getRandom(-1000, 1000);
        Enemy[i].posY = getRandom(-1000, 1000);
        Enemy[i].posA = getRandom(0,359);
        Enemy[i].velX = 0;
        Enemy[i].velY = 0;
        Enemy[i].velA = 0;
        Enemy[i].impFB = 0;
        Enemy[i].impLR = 0;
        Enemy[i].impA = 0;
        Enemy[i].impFlevel = SHIP_IMPULSE_F;
        Enemy[i].impBlevel = SHIP_IMPULSE_B;
        Enemy[i].impAlevel = SHIP_IMPULSE_A;
        Enemy[i].impLlevel = SHIP_IMPULSE_L;
        Enemy[i].impRlevel = SHIP_IMPULSE_R;
        Enemy[i].decA = SHIP_TURN_DECAY;
        Enemy[i].decXY = SHIP_VEL_DECAY;
        Enemy[i].maxVel = SHIP_MAX_VEL;
        Enemy[i].maxTurnVel = SHIP_MAX_TURN_VEL;

        Enemy[i].texture = Game.loadTexture("graphics/ship2.png");
    }

    Game.mainViewport.scale = 1;
    Game.mainViewport.windowHeight = MAIN_VIEWPORT_HEIGHT;
    Game.mainViewport.windowWidth = MAIN_VIEWPORT_WIDTH;
    Game.mainViewport.windowHeightHalf = MAIN_VIEWPORT_HEIGHT / 2;
    Game.mainViewport.windowWidthHalf = MAIN_VIEWPORT_WIDTH / 2;
    Game.mainViewport.windowX = MAIN_VIEWPORT_X;
    Game.mainViewport.windowY = MAIN_VIEWPORT_Y;
    Game.mainViewport.padding = VIEWPORT_PADDING;
    Game.mainViewport.shiftSpeed = VIEWPORT_SHIFT_SPEED;

    Game.dataViewport.scale = 1;
    Game.dataViewport.windowHeight = DATA_VIEWPORT_HEIGHT;
    Game.dataViewport.windowWidth = DATA_VIEWPORT_WIDTH;
    Game.dataViewport.windowHeightHalf = DATA_VIEWPORT_HEIGHT / 2;
    Game.dataViewport.windowWidthHalf = DATA_VIEWPORT_WIDTH / 2;
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