#include <iostream>
#include <math.h>

#include "objects.h"
#include "defs.h"
#include "engine.h"
#include "stars.h"

using namespace std;

extern spacegame Game;
//extern spaceobject Enemy[MAXNUMENEMIES];
extern spaceplayer Player;
extern spaceobject Ship;
//extern spaceobject Explosion[MAXNUMEXPLOSIONS];
//extern spaceobject Laser[MAXNUMLASERS];
//extern spaceobject HealthAmmo[MAXNUMHEALTHAMMO];

extern Uint32 frameStart;
extern int frameTime;
extern Uint32 frames;

void ProcessInputs()
{
    if(Game.usrArrowUp)
    {
        Ship.impFB += Ship.impFlevel;
        Game.usrArrowUp = false;
    }

    if(Game.usrArrowDown)
    {
        Ship.impFB -= Ship.impBlevel;
        Game.usrArrowDown = false;
    }

    if(Game.usrArrowLeft)
    {
        Ship.impA += Ship.impAlevel;
        Game.usrArrowLeft = false;
    }

    if(Game.usrArrowRight)
    {
        Ship.impA -= Ship.impAlevel;
        Game.usrArrowRight = false;
    }

    if(Game.usrKeyPageDown)
    {
        Ship.impLR -= Ship.impLlevel;
        Game.usrKeyPageDown = false;
    }

    if(Game.usrKeyPageUp)
    {
        Ship.impLR += Ship.impRlevel;
        Game.usrKeyPageUp = false;
    }

    if(Game.usrKeySpacebar)
    {
        Player.fireLaser = true;
        Game.usrKeySpacebar = false;
    }

    if(Game.usrKeyEscape)
    {
        if(Player.inMenu)
        {
            Player.inGame = true;
            Player.inMenu = false;
            std::cout << "Back to Game" << std::endl;
        }
        else if(Player.inGame)
        {
            Player.inGame = false;
            Player.inMenu = true;
            std::cout << "Leaving Game" << std::endl;
        } 
        Game.usrKeyEscape = false;
        
    }

    if(Game.usrKeyX)
    {
        if(Player.inMenu)
        {
            Game.isPlaying = false;
            std::cout << "Quitting" << std::endl;
        }
        Game.usrKeyX = false;
    }

    // if(Game.usrKeyN)
    // {
    //     Game.usrKeyN = false;
    // }
    
    if(Game.usrKeyP)
    {
        Game.usrKeyP = false;
        // std::cout << "Main X: " << Game.mainViewport.windowX << std::endl;
        // std::cout << "Main Y: " << Game.mainViewport.windowY << std::endl;
        // std::cout << "Main W: " << Game.mainViewport.windowWidth << std::endl;
        // std::cout << "Main H: " << Game.mainViewport.windowHeight << std::endl;
        // std::cout << "Data X: " << Game.dataViewport.windowX << std::endl;
        // std::cout << "Data Y: " << Game.dataViewport.windowY << std::endl;
        // std::cout << "Data W: " << Game.dataViewport.windowWidth << std::endl;
        // std::cout << "Data H: " << Game.dataViewport.windowHeight << std::endl;

        // Game.mainViewport.windowX += 10;

        Game.mainViewport.scale += .5;

    }
}

void HandlePlayerShip()
{
    Ship.updatePosition();
    Ship.decayVelocity();
    //Ship.nudgeY(SHIPREST, NUDGEAMOUNT);

    //Monitor Player Position
    // if(Ship.posX < MINX_PLAYABLE_AREA){Ship.posX = MINX_PLAYABLE_AREA;}
    // if(Ship.posX > MAXX_PLAYABLE_AREA){Ship.posX = MAXX_PLAYABLE_AREA;}
    // if(Ship.posY < MINY_PLAYABLE_AREA){Ship.posY = MINY_PLAYABLE_AREA;}
    // if(Ship.posY > MAXY_PLAYABLE_AREA){Ship.posY = MAXY_PLAYABLE_AREA;}
}

void CheckHighScore()
{
//     if(Player.score > Player.highScore)
//     {
//         Player.highScore = Player.score;
//         Game.writeHighScore(Player.highScore);
//     }
}

// void MakeExplosion(float x, float y, float vx, float vy, int col)
// {
//     for(int i = 0; i < MAXNUMEXPLOSIONS; i++)
//     {
//         if(!Explosion[i].active)
//         {
//             Explosion[i].active = true;
//             Explosion[i].x = x;
//             Explosion[i].y = y;
//             Explosion[i].color = col;
//             Explosion[i].stage = 0;
//             Explosion[i].velX = vx;
//             Explosion[i].velY = vy;
//             i = MAXNUMEXPLOSIONS;
//         }
//     }
    
// }

// void MakeLaser(float x, float y, float vx, float vy, int col)
// {
//     for(int i = 0; i < MAXNUMLASERS; i++)
//     {
//         if(!Laser[i].active)
//         {
//             Laser[i].active = true;
//             Laser[i].x = x;
//             Laser[i].y = y;
//             Laser[i].color = col;
//             Laser[i].objectType = col;
//             Laser[i].stage = 0;
//             Laser[i].velX = vx;
//             Laser[i].velY = vy;
//             i = MAXNUMLASERS;
//         }
//     }
// }

// void KillEnemy(int num)
// {
//     //Enemy[0]
//     //Enemy[1]
//     //Enemy[2]
//     //Enemy[3]
//     //Enemy[4]

//     for(int i = num; i < Player.numEnemyShips; i++)
//     {
//         Enemy[i] = Enemy[i+1];
//     }
//     Player.numEnemyShips--;
// }

// void RandomizeEnemy(int num)
// {
//     Enemy[num].x = Game.getRandom(MINX, MAXX);
//     Enemy[num].y = MINY;
//     Enemy[num].velX = Game.getRandom(MINVELX, MAXVELX);
//     Enemy[num].velY = Game.getRandom(MINVELY, MAXVELY);
// }






// void HandleShips()
// {  


    //Monitor Enemy Positions
    // for(int i=0; i < Player.numEnemyShips; i++)
    // {
    //     Enemy[i].updatePosition();

    //     //Loop to other edge of screen
    //     if(Enemy[i].x > MAXX){Enemy[i].x = MINX;}
    //     if(Enemy[i].x < MINY){Enemy[i].x = MAXX;}

    //     //Reset if they get to end of screen
    //     if(Enemy[i].y > MAXY)
    //     {
    //         RandomizeEnemy(i);
    //     }

    //     //Randomly Fire Laser
    //     if(int(rand() % ENEMYFIRECHANCE) == 10)
    //     {
    //         Game.playSound(2);
    //         MakeLaser(Enemy[i].x, Enemy[i].y, Enemy[i].velX * LASERVELXDAMPING,Enemy[i].velY + LASERVELENEMY, 2);
    //     }
   
    //     //Detect enemy collisions w/ player
    //     if(fabs(Ship.x - Enemy[i].x) < COLDISTANCEX && fabs((Ship.y+8)-Enemy[i].y) < COLDISTANCEY)
    //     {   
    //         MakeExplosion(Enemy[i].x, Enemy[i].y - 8, Enemy[i].velX, Enemy[i].velY, 1);
    //         //sound damage
    //         KillEnemy(i);
    //         Player.health = Player.health - HEALTHDECREASEINCREMENT;
    //         Game.playSound(7);
    //     }
    // }
// }

// void InitEnemies()
// {
//     for(int i=0; i < Player.numEnemyShips; i++)
//     {
//         RandomizeEnemy(i);
//     }
// }

// void CheckEnemyNumbers()
// {
//     if(!Player.numEnemyShips)
//     {
//         for(int i = 0; i < Player.shipToAdd; i++)
//         {
//             if(Player.numEnemyShips < MAXNUMENEMIES)
//             {
//                 Player.numEnemyShips++;
//                 RandomizeEnemy(i);
//                 //Enemy[i].active = true;
//             }
//         }
    
//        Player.shipToAdd += 10; 
//        Game.playSound(3);
//     }
// }

// void CheckEndOfGame()
// {
//     if(Player.health <= 0)
//     {
//         if(Player.endOfGameStage % 15 == 0)
//         {
//             for(int i = 0; i < 2; i++)
//             {
//                 MakeExplosion(Ship.x + Game.getRandom(-10, 10), Ship.y + Game.getRandom(-10, 10), Ship.velX, Ship.velY, 1);
//             }
//         }
//         Player.endOfGameStage++;
//         if(Player.endOfGameStage==1) Game.playSound(4);
//         if(Player.endOfGameStage > 100)
//         {
//             Player.inWaitingToContinue = true;
//             while(Player.inWaitingToContinue)
//             {
//                 frameStart = SDL_GetTicks();
                
//                 if(Game.usrKeyC || Game.usrKeyX)
//                 {
//                     Player.inWaitingToContinue=false;
//                     Game.usrKeyC=false;
//                     Game.playSound(3);
//                 }
//                 //HandleStars();
//                 Game.handleEvents();
//                 Game.render();

//                 frames++;
//                 frameTime = SDL_GetTicks() - frameStart;
//                 if(frameDelay > frameTime){SDL_Delay(frameDelay - frameTime);}

//             }
            
//             Player.inGame=false;
//             Game.playSound(3);
//         }
//     }
// }

// void HandleLasers()
// {
//     //See if a new laser needs to be fired
//     if(Player.fireLaser && Player.ammo)
//     {
//         Game.playSound(1);
//         MakeLaser(Ship.x, Ship.y, Ship.velX * LASERVELXDAMPING, Ship.velY - LASERVEL, 1);
//         Player.ammo--;
//     }
//     Player.fireLaser=false;

//     //Update Positions and put inactive if out of bounds
//     for(int i = 0; i < MAXNUMLASERS; i++)
//     {
//         if(Laser[i].active)
//         {
//             Laser[i].updatePosition();
//             if(Laser[i].y < MINY || Laser[i].y > MAXY || Laser[i].x > MAXX || Laser[i].x < MINY)
//             {
//                 Laser[i].active = false;
//             }
//         }
//     }

//     //Detect enemy collisions w/ lasers
//     for(int i = 0; i < MAXNUMLASERS; i++)
//     {
//         if(Laser[i].active && Laser[i].objectType == 1)
//         {
//             for(int j = 0; j < Player.numEnemyShips; j++)
//             {
//                 if((fabs(Laser[i].x - Enemy[j].x) < COLDISTANCEX) && (fabs(Laser[i].y-Enemy[j].y) < COLDISTANCEY))
//                 {
//                     //Collision Has Happened
//                     MakeExplosion(Enemy[j].x, Enemy[j].y - 8 , Enemy[j].velX, Enemy[j].velY, 1);
//                     Game.playSound(8);
//                     KillEnemy(j);
//                     Player.ammo += 2;
//                     Player.kills++;
//                     Player.score += 100;

//                 }
//             }
//         }

//         //Detect player collision w/ enemy laser
//         if(Laser[i].active && Laser[i].objectType == 2)
//         {
//             if((fabs(Laser[i].x - (Ship.x)) < COLDISTANCEX) && (fabs(Laser[i].y-Ship.y) < COLDISTANCEY))
//             {
//                 //Collision Has Happened
//                 MakeExplosion(Ship.x, Ship.y + 8 , Ship.velX,Ship.velY, 1);
//                 Player.health -= 10;
//                 Laser[i].active = false;
//                 Game.playSound(7);

//             } 
//         }

//     }

// }

// void HandleExplosions()
// {
//     for(int i=0; i < MAXNUMEXPLOSIONS; i++)
//     {
//         if(Explosion[i].active)
//         {
//             Explosion[i].updatePosition();
//             Explosion[i].stage++;
//             if(Explosion[i].stage > EXPLOSIONSIZE)
//             {
//                 Explosion[i].active=false;
//             }
//         }
//     }
// }

// void HandleHealthAmmo()
// {
//     //Randomly spawn
//     if(int(rand() % HEALTHAMMOCHANCE) == 100)
//     {
//         //Find first available
//         for(int i = 0; i < MAXNUMHEALTHAMMO; i++)
//         {
//             if(!HealthAmmo[i].active)
//             {
//                 HealthAmmo[i].active = true;
//                 HealthAmmo[i].x = Game.getRandom(MINX,MINY);
//                 HealthAmmo[i].y = MINY;
//                 HealthAmmo[i].velX = Game.getRandom(0, MAXVELX);
//                 HealthAmmo[i].velY = Game.getRandom(MINVELY, MAXVELY);

//                 //cout << "H/A SPAWN " << i << " X= " << HealthAmmo[i].x << " Y= " << HealthAmmo[i].y;
//                 //cout << " XVEL: " << HealthAmmo[i].velX << " YVEL: " << HealthAmmo[i].velY << endl;
          
//                 i = MAXNUMHEALTHAMMO;
//             }
//         }
//     }

//     if(int(rand() % AMMOCHANCE) == 10)
//     {
//         Player.ammo++;
//     }

//     if(int(rand() % AMMOCHANCE) == 10)
//     {
//         if(Player.health < 20) Player.health++;
//     }
    
//     //Update Position and Check Rules
//     for(int i = 0; i < MAXNUMHEALTHAMMO; i++)
//     {
//         if(HealthAmmo[i].active)
//         {
//             //Set inactive if out of bounds
//             HealthAmmo[i].updatePosition();
//             if(HealthAmmo[i].x < MINX){HealthAmmo[i].active=false;}
//             if(HealthAmmo[i].x > MAXX){HealthAmmo[i].active=false;}
//             if(HealthAmmo[i].y > MAXY){HealthAmmo[i].active=false;}

//             //Detect laser collisions
//             for(int j = 0; j < MAXNUMLASERS; j++)
//             {
//                 if((fabs(Laser[j].x - HealthAmmo[i].x) < COLDISTANCEX) && (fabs(Laser[j].y-HealthAmmo[i].y) < COLDISTANCEY) && Laser[j].active && Laser[j].objectType == 1)
//                 {
//                     MakeExplosion(HealthAmmo[i].x,HealthAmmo[i].y, HealthAmmo[i].velX, HealthAmmo[i].velY, 2);
//                     HealthAmmo[i].active=false;
//                     Player.health = Player.health - 5;
//                     Game.playSound(9);
//                     //cout << "HealthAmmo laser collision\n";
//                 }
//             }

//             if((fabs(Ship.x - HealthAmmo[i].x) < COLDISTANCEXHEALTH) && (fabs((Ship.y+8)-HealthAmmo[i].y) < COLDISTANCEYHEALTH))
//             {
//                 MakeExplosion(HealthAmmo[i].x,HealthAmmo[i].y, HealthAmmo[i].velX, HealthAmmo[i].velY, 2);
//                 HealthAmmo[i].active=false;
//                 Player.health += 10;
//                 Player.ammo += 50;
//                 Player.score += 500;
//                 Game.playSound(5);
//                 //cout << "HealthAmmo ship collision\n";
//             }    
//         }

    
//     }


// }



