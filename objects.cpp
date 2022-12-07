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

    velX -= (sin(posA) * impFB);
    velY += (cos(posA) * impFB);
    impFB = 0;

    velX += (cos(posA) * impLR);
    velY -= (sin(posA) * impLR);

    impLR = 0;

    if(velX > maxVel) velX = maxVel;
    if(velX < -maxVel) velX = -maxVel;
    if(velY > maxVel) velY = maxVel;
    if(velY < -maxVel) velY = -maxVel;

    posX += velX;
    posY += velY;
    posA += velA;

    if(posA > TWOPIRAD){ posA -= TWOPIRAD; }
    if(posA < 0){ posA +- TWOPIRAD; }

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

void spaceobject::rotateGraphics()
{
    
    //Start with clear Pallete
    graphicRotated.clear();
    
    for(const straightline&i : graphic)
    {
        float newx1 = ( i.x1 * cos(posA) * Game.mainViewport.scale - i.y1 * sin(posA) * Game.mainViewport.scale);
        float newy1 = ( i.x1 * sin(posA) * Game.mainViewport.scale + i.y1 * cos(posA) * Game.mainViewport.scale);

        float newx2 = ( i.x2 * cos(posA) * Game.mainViewport.scale - i.y2 * sin(posA) * Game.mainViewport.scale);
        float newy2 = ( i.x2 * sin(posA) * Game.mainViewport.scale + i.y2 * cos(posA) * Game.mainViewport.scale);

        graphicRotated.push_back(straightline(newx1,newy1,newx2,newy2,i.r,i.g,i.b));
             
    }

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