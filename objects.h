#pragma once
#include <SDL2/SDL.h>
#include "defs.h"

using namespace std;

// Stuff that moves around on the screen

class spaceobject
{
    public:
        float posX, posY, posA, velX, velY, velTotal, velA, impFB, impLR, impA;
        float maxVel, maxTurnVel;

        int height, width;

        float scale;

        
        
        float decA, decXY;

        float impFlevel, impBlevel, impLlevel, impRlevel, impAlevel;

        char callsign[MAX_CALLSIGN_LEN];

        //int color;
        bool active;
        //int stage;
        int life;

        //Uint32 lastUpdate;

        SDL_Texture *texture;

        //int objectType;

        void updatePosition();
        void simpleUpdatePosition();
        void decayVelocity();

        void clear();

    private:

};

//Human Sitting in Front of Keyboard
class spaceplayer
{
    public:
        int ammo, health, score, kills;

        bool fireLaser;
        bool inGame, inMenu, inWaitingToContinue;

};