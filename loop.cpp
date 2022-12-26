#include <SDL2/SDL.h>
//#include <vector>

#include "loop.h"
#include "engine.h"
#include "objects.h"
#include "defs.h"
#include "draw.h"
#include "mechanics.h"
#include "stars.h"
#include "util.h"
#include "inputs.h"

using namespace std;

Uint32 frameStart;
Uint32 frameTime;
extern Uint32 frames;

extern spacegame Game;

spaceplayer Player;
spaceobject Ship;
spaceobject Star[NUM_STARS];
spaceobject Enemy[MAX_NUM_ENEMIES];
spaceobject Laser[MAX_NUM_LASERS];
spaceobject Explosion[MAX_NUM_EXPLOSIONS];

void GameLoop()
{
    Init();
    
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
            UpdatePlayerShip();
            UpdateEnemies();
            UpdateLasers();
            UpdateExplosions();

            UpdateViewport();
            
        }

        if(Player.inMenu) MenuLoop();

        Game.renderClear();
        Draw();
        Game.renderPresent();

        // Limit to 60 frameas per second
        frames++;
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){SDL_Delay(frameDelay - frameTime);}
        else{std::cout << "Frames Lost" << std::endl;}
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
        std::cout << "N PRESSED" << std::endl;
        InitNewGame();
    }

    if(Game.usrKeyX)
    {
        Game.isPlaying = false;
        Game.usrKeyX = false;
    }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void Init()
{
    // Loading Screen here?
    Game.loadFont(0, "fonts/dos.ttf", DEF_FONT_SIZE);
    Game.loadFont(1, "fonts/squared.ttf", 12);
    InitViewports();
    Game.isPlaying = true;
    Player.inMenu = true;
    Player.inGame = false;
    Game.setKeysOff();
    InitStars();
}

void InitNewGame()
{
    std::cout << "New Game Started" << std::endl;   

    Player.fireLaser = false; 

    Game.mainViewport.scale = 2;
    Game.mainViewport.userScale = 0;
    Game.setKeysOff();


    Ship.clear();
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

    Ship.texture = Game.loadTexture("graphics/ship1.png");
    SDL_QueryTexture(Ship.texture, NULL, NULL, &Ship.width, &Ship.height);
    
    //for(spaceobject i : Enemy)
    for(int i = 0; i < MAX_NUM_ENEMIES; i++)
    {
        Enemy[i].clear();
        Enemy[i].active = true;
        Enemy[i].posX = getRandom(-500, 500);
        Enemy[i].posY = getRandom(-500, 500);
        Enemy[i].posA = getRandom(0,359);
        Enemy[i].velX = getRandom(-1,3);
        Enemy[i].impFlevel = SHIP_IMPULSE_F;
        Enemy[i].impBlevel = SHIP_IMPULSE_B;
        Enemy[i].impAlevel = SHIP_IMPULSE_A;
        Enemy[i].impLlevel = SHIP_IMPULSE_L;
        Enemy[i].impRlevel = SHIP_IMPULSE_R;
        Enemy[i].decA = SHIP_TURN_DECAY;
        Enemy[i].decXY = SHIP_VEL_DECAY;
        Enemy[i].maxVel = SHIP_MAX_VEL;
        Enemy[i].maxTurnVel = SHIP_MAX_TURN_VEL;
        strcpy(Enemy[i].callsign, "TANGO");

        std::cout << Enemy[i].callsign << std::endl;

        Enemy[i].texture = Game.loadTexture("graphics/ship2.png");
        SDL_QueryTexture(Enemy[i].texture, NULL, NULL, &Enemy[i].width, &Enemy[i].height);
    }

    for(int l = 0; l < MAX_NUM_LASERS; l++)
    {
        Laser[l].clear();
    }

    for(int e = 0; e < MAX_NUM_EXPLOSIONS; e++)
    {
        Explosion[e].clear();
        Explosion[e].texture = Game.loadTexture("graphics/explosion1.png");
    }

    Game.setKeysOff();
}

void InitViewports()
{
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
}