#include <stdlib.h>

#include "stars.h"
#include "defs.h"
#include "objects.h"
#include "engine.h"

extern spaceobject Star[NUMSTARS];
extern spacegame Game;
extern spaceplayer Player;
extern spaceobject Ship;


void InitStars()
{
    for(int i = 0; i < NUMSTARS; i++)
    {
        Star[i].posX = Game.getRandom(0, WINDOW_WIDTH);
        Star[i].posY = Game.getRandom(0, WINDOW_HEIGHT);
        Star[i].velY = Game.getRandom(MINSTARVEL, MAXSTARVEL);
    }
}

void HandleStars()
{
    if(Player.inMenu)
    {
        for(int i = 0; i < NUMSTARS; i++)
        {
            //Update the stars position based on Velocity
            Star[i].posY += Star[i].velY;
            if(Star[i].posY > WINDOW_HEIGHT) {Star[i].posY = 0;}
        }
    }

    if(Player.inGame)
    {
        for(int i = 0; i < NUMSTARS; i++)
        {
            Star[i].posX -= (Ship.velX * STARVELRATIO * Star[i].velY);
            Star[i].posY += (Ship.velY * STARVELRATIO * Star[i].velY);

            if(Star[i].posX > WINDOW_WIDTH) {Star[i].posX = 0;}
            if(Star[i].posX < 0) {Star[i].posX = WINDOW_WIDTH;}
            if(Star[i].posY > WINDOW_HEIGHT) {Star[i].posY = 0;}
            if(Star[i].posY < 0) {Star[i].posY = WINDOW_HEIGHT;}
        }
    }

}