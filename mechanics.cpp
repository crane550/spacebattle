#include <iostream>
#include <math.h>

#include "mechanics.h"
#include "objects.h"
#include "defs.h"
#include "engine.h"
#include "stars.h"
#include "util.h"

using namespace std;

extern spacegame Game;
extern spaceplayer Player;
extern spaceobject Ship;
extern spaceobject Enemy[MAX_NUM_ENEMIES];
extern spaceobject Laser[MAX_NUM_LASERS];
extern spaceobject Explosion[MAX_NUM_EXPLOSIONS];

// extern Uint32 frameStart;
// extern int frameTime;
// extern Uint32 frames;

void UpdatePlayerShip()
{
    if(Player.fireLaser)
    {
        // Find 1st Available Laser
        
        for(int l = 0; l < MAX_NUM_LASERS; l++)
        {
            if(!Laser[l].active)
            {
                Laser[l].clear();
                Laser[l].active = true;
                Laser[l].posX = Ship.posX + (sin(Ship.posA * RAD_TO_DEG) * LASER_BUFFER);
                Laser[l].posY = Ship.posY + (cos(Ship.posA * RAD_TO_DEG) * LASER_BUFFER);
                Laser[l].velX = Ship.velX;
                Laser[l].velY = Ship.velY;
                Laser[l].posA = Ship.posA;
                Laser[l].impFB = LASER_VEL;
                Laser[l].life = LASER_LIFE;
                Laser[l].height = 1;
                Laser[l].width = 1;
                
                break;
            }
        }
        Player.fireLaser = false;
    }
    
    Ship.updatePosition();
    Ship.decayVelocity();
}

void UpdateEnemies()
{
    for(int e = 0; e < MAX_NUM_ENEMIES; e++)
    {
        if(Enemy[e].active)
        {
            Enemy[e].updatePosition();
            Enemy[e].decayVelocity();

            // Check for Laser collision
            for(int l = 0; l < MAX_NUM_LASERS; l++)
            {
                if (Laser[l].active)
                {
                    if (checkHypCollision(Enemy[e],Laser[l]))
                    {
                        //std::cout << "COLLISION: Enemy " << e << " Laser " << l << std::endl; 
                        Laser[l].active = false;
                        Enemy[e].active = false;

                        MakeExplosion(Enemy[e]);

                    }
                }           
            }
        }

    }
}

void MakeExplosion(spaceobject& so)
{
    int explosionsmade = 0;
    for(int e = 0; e < MAX_NUM_EXPLOSIONS; e++)
    {
        
        if(!Explosion[e].active)
        {
            Explosion[e].clear();

            Explosion[e].active = true;
            Explosion[e].posX = so.posX + getRandom(-10,10);
            Explosion[e].posY = so.posY + getRandom(-10,10);
            Explosion[e].posA = getRandom(0,359);
            Explosion[e].velX = so.velX + getRandom(-0.2,0.2);
            Explosion[e].velY = so.velY + getRandom(-0.2,0.2);
            Explosion[e].velA = getRandom(-1,1);

            Explosion[e].life = int(getRandom(10,40));
            Explosion[e].scale = (getRandom(.6,1.3));

            SDL_QueryTexture(Explosion[e].texture, NULL, NULL, &Explosion[e].width, &Explosion[e].height);
            Explosion[e].width *= Explosion[e].scale;
            Explosion[e].height *= Explosion[e].scale;

            std::cout << "EXPLOSION MADE " << e << " LIFE: " << Explosion[e].life << std::endl;

            explosionsmade++;
            if(explosionsmade > NUM_EXPLOSIONS)
            {
                break;
            }

            //return;
           
        }

    }
}

void UpdateExplosions()
{
    for(int e = 0; e < MAX_NUM_EXPLOSIONS; e++)
    {
        if(Explosion[e].active)
        {
            Explosion[e].simpleUpdatePosition();
            Explosion[e].life--;
        }
        
        if(Explosion[e].life <= 0) Explosion[e].active = false;
        
    }
}

void UpdateLasers()
{
    for(int i = 0; i < MAX_NUM_LASERS; i++)
    {
        if(Laser[i].active)
        {
            Laser[i].simpleUpdatePosition();
            Laser[i].life--;
        }

        // Check for laser end of life
        if(Laser[i].life <= 0) Laser[i].active = false;

    }
}