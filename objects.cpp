#include <stdlib.h>
#include <math.h>
#include "defs.h"
#include "objects.h"
#include "engine.h"

extern spaceobject Ship;
extern spacegame Game;

void spaceobject::updatePosition()
{
    velA += impA;
    impA = 0;

    if(velA > maxTurnVel) velA = maxTurnVel;
    if(velA < -maxTurnVel) velA = -maxTurnVel;

    posA += velA;

    if(posA > 360){ posA -= 360; }
    if(posA < 0){ posA += 360; }

    velX += (sin(posA * RAD_TO_DEG) * impFB);
    velY += (cos(posA * RAD_TO_DEG) * impFB);
    impFB = 0;

    velX += (cos(posA * RAD_TO_DEG) * impLR);
    velY -= (sin(posA * RAD_TO_DEG) * impLR);

    impLR = 0;

    // Too slow?
    velTotal = SDL_sqrtf(velX * velX + velY * velY);

    // Speed Limit
    if(velTotal > maxVel)
    {
        velX = maxVel * sin(posA * RAD_TO_DEG);
        velY = maxVel * cos(posA * RAD_TO_DEG);
    }

    // Finally, update position
    posX += velX;
    posY += velY;

}

void spaceobject::decayVelocity()
{
    velX *= decXY;
    velY *= decXY;
    velA *= decA;
}

void spaceobject::nudgeY(float ypos, float inc)
{
    // if(y > ypos){y -= inc;}
    // if(y < ypos){y += inc;}   
}

// void spaceobject::RandomizeVelX(float minvel, float maxvel)
// {
//     velX = Rando(minvel, maxvel)
// }

// void spaceobject::RandomizeVelY(float maxvel)
// {
//     velY = (rand() % 2) + 1;
// }

// void spaceobject::RandomizePosition(float maxX, float maxY)
// {
//     x = Rando(0, maxX);
//     y = Rando(0, maxY);
// }

// void spaceobject::RandomizePositionX(float maxX)
// {
//     x = Rando(0, maxX);
// }