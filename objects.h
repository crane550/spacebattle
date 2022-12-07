#pragma once
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

// Stuff that moves around on the screen
class straightline
{
    public:

        float x1, y1, x2, y2;
        
        int r, g, b;
        
        int o;

        straightline(float vx1, float vy1, float vx2, float vy2, int cr, int cg, int cb)
        {
            x1 = vx1; y1 = vy1; x2 = vx2; y2 = vy2; r = cr; g = cg; b = cb;
        }

    private:

};

class spaceobject
{
    public:
        float posX, posY, posA, velX, velY, velA, impFB, impLR, impA;

        float maxVel, maxTurnVel;
        
        float decA, decXY;

        float impFlevel, impBlevel, impLlevel, impRlevel, impAlevel;



        int color;
        bool active;
        int stage;

        Uint32 lastUpdate;

        vector<straightline> graphic;
        vector<straightline> graphicRotated;

        int objectType;

        void updatePosition();
        //void RandomizePosition(float, float);
        //void RandomizePositionX(float);
        void decayVelocity();
        void nudgeY(float,float);
        void rotateGraphics();
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