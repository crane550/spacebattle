#pragma once
#include <SDL2/SDL.h>
//#include <vector>

using namespace std;

// Stuff that moves around on the screen

class spaceobject
{
    public:
        float posX, posY, posA, velX, velY, velTotal, velA, impFB, impLR, impA;

        float maxVel, maxTurnVel;
        
        float decA, decXY;

        float impFlevel, impBlevel, impLlevel, impRlevel, impAlevel;

        int color;
        bool active;
        int stage;

        Uint32 lastUpdate;

        SDL_Texture *texture;

        int objectType;

        void updatePosition();
        void decayVelocity();
        void nudgeY(float,float);

        //void RandomizePosition(float, float);
        //void RandomizePositionX(float);
        //void RandomizeVelX(float);
        //void RandomizeVelY(float);

    private:

};

//Human Sitting in Front of Keyboard
class spaceplayer
{
    public:
        int ammo, health, score, kills;

        bool fireLaser;
        bool inGame, inMenu, inWaitingToContinue;

        int endOfGameStage;
        int highScore;
};

        //Lasers
        //Type 1 = Friendly
        //Type 2 = Enemy

        //Health/Amm0
        //Type 1 = Standard
        //Type 2 = Ammo only
        //Type 3 = Health Only

        //Explosion
        //Color 1 = red Explosion
        //Color 2 = Green explosion