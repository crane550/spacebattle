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

void spaceobject::simpleUpdatePosition()
{
    if(impFB)
    {
        velX += (sin(posA * RAD_TO_DEG) * impFB);
        velY += (cos(posA * RAD_TO_DEG) * impFB);
        impFB = 0;
    }

    // Finally, update position
    posX += velX;
    posY += velY;
    posA += velA;
    
    if(posA > 360){ posA -= 360; }
    if(posA < 0){ posA += 360; }

}

void spaceobject::decayVelocity()
{
    velX *= decXY;
    velY *= decXY;
    velA *= decA;
}

void spaceobject::clear()
{
    active = false;
    posX = 0;
    posY = 0;
    posA = 0;
    velX = 0;
    velY = 0;
    velTotal = 0;
    velA = 0;
    impFB = 0;
    impLR = 0;
    impA = 0;
    maxVel = 0;
    maxTurnVel = 0;
    decA = 0;
    decXY = 0;
    impFlevel = 0;
    impBlevel = 0;
    impRlevel = 0;
    impAlevel = 0;
    life = 0;
    height = 0;
    width = 0;

}