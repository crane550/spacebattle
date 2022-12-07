#include <math.h>
#include <vector>
#include <string>
#include "draw.h"
#include "engine.h"
#include "defs.h"
#include "objects.h"

////////////////////////////////////////////////////////
////////////////////THINGS TO DRAW//////////////////////
////////////////////////////////////////////////////////

using namespace std;

extern spacegame Game;
extern spaceplayer Player;
extern spaceobject Ship;
extern spaceobject Star[NUMSTARS];
extern vector<straightline> ufo;

//extern spaceobject Explosion[MAXNUMEXPLOSIONS];
//extern spaceobject Enemy[MAXNUMENEMIES];
//extern spaceobject Laser[MAXNUMLASERS];
//extern spaceobject HealthAmmo[MAXNUMHEALTHAMMO];

void Draw()
{    
    //Draw the Stars
    for(int i = 0; i < NUMSTARS; i++)
    {
        Game.drawPoint(Game.mainViewport, Star[i].posX, Star[i].posY, 0, 255, 255);
    }

    if(Player.inGame)
    {        
        //Draw Ship     
        DrawObject(Ship, Game.mainViewport);
     
        //Draw In Game Text
        DrawGameText();

        DrawBorder(Game.dataViewport);
        DrawBorder(Game.mainViewport);
        //DrawBorder(Game.testvp);

    }

    if(Player.inMenu)
    {       
        Game.putText(Game.mainViewport,"Space Battle!", 1, 250, 150, 255,255, 0);
        Game.putText(Game.mainViewport,"(N)ew Game", 1, 250, 180, 0, 255, 0);
        Game.putText(Game.mainViewport,"e(X)it", 1, 250, 210, 255, 0, 0);
    }

    if(Player.inWaitingToContinue)
    {
        // Game.putText("Game Over!", 1, 270, 200, 255, 0, 0);
        // Game.putText("(C)ontinue...", 1, 270,240,0,255,0);
    }

}

void DrawObject(spaceobject& object, viewport& vp)
{ 
    object.rotateGraphics();

    int x = object.posX - vp.focusX;
    int y = vp.focusY - object.posY;

    //Make sure it's near window or at least close
    if (x < -VIEWPORT_BUFFER) return;
    if (x > vp.windowWidth + VIEWPORT_BUFFER) return;
    if (y < -VIEWPORT_BUFFER) return;
    if (y > vp.windowHeight + VIEWPORT_BUFFER) return;


    // Looks good, go ahead and draw
    for(int i = 0; i < object.graphicRotated.size(); i++)
    {
        Game.drawLine(Game.mainViewport,    x + object.graphicRotated[i].x1,
                                            y - object.graphicRotated[i].y1,
                                            x + object.graphicRotated[i].x2,
                                            y - object.graphicRotated[i].y2,
                                            object.graphicRotated[i].r,
                                            object.graphicRotated[i].g,
                                            object.graphicRotated[i].b);
    }




    // int x = vp.focusX - object.posX;
    // int y = vp.focusY - object.posY;

    // //Make sure it's near window or at least close
    // if(x < abs(vp.windowWidth + VIEWPORT_BUFFER ) && y < (vp.windowWidth + VIEWPORT_BUFFER ) )
    // {
    //     for(int i = 0; i < object.graphicRotated.size(); i++)
    //     {
    //         Game.drawLine(Game.mainViewport,    x + object.graphicRotated[i].x1,
    //                                             y - object.graphicRotated[i].y1,
    //                                             x + object.graphicRotated[i].x2,
    //                                             y - object.graphicRotated[i].y2,
    //                                             object.graphicRotated[i].r,
    //                                             object.graphicRotated[i].g,
    //                                             object.graphicRotated[i].b);
    //     }

    // }
  
}

void DrawBorder(viewport& vp)
{
    Game.drawLine(vp, 0, 0, vp.windowWidth, 0, 120, 120, 120);
    Game.drawLine(vp, vp.windowWidth, 0, vp.windowWidth, vp.windowHeight, 120, 120, 120);
    Game.drawLine(vp, vp.windowWidth, vp.windowHeight, 0, vp.windowHeight, 120, 120, 120);
    Game.drawLine(vp, 0,vp.windowHeight, 0, 0, 120, 120, 120);

    // Game.drawLine(vp, vp.windowX, vp.windowY, vp.windowX + vp.windowWidth, vp.windowY, 180, 180, 180);
    // Game.drawLine(vp, vp.windowX + vp.windowWidth, vp.windowY, vp.windowX + vp.windowWidth, vp.windowY + vp.windowHeight, 180, 180, 180);
    // Game.drawLine(vp, vp.windowX + vp.windowWidth, vp.windowY + vp.windowHeight, vp.windowX, vp.windowY + vp.windowHeight, 180, 180, 180);
    // Game.drawLine(vp, vp.windowX, vp.windowY + vp.windowHeight, vp.windowX, vp.windowY, 180, 180, 180);


    return;

}

void DrawGameText()
{
    Game.putText(Game.dataViewport,"X:", 0, 10, 5, 255, 0, 255);
    Game.putText(Game.dataViewport,std::to_string(Ship.posX), 0, 70, 5, 255, 255, 255);
    
    Game.putText(Game.dataViewport,"Y: ",0, 10, 25, 0, 255,0);
    Game.putText(Game.dataViewport,std::to_string(Ship.posY), 0, 70, 25, 255, 255, 255);  

    Game.putText(Game.dataViewport,"A: ",0, 10, 45, 255, 0,0);
    Game.putText(Game.dataViewport,std::to_string(Ship.posA), 0, 70, 45, 255, 255, 255);

    Game.putText(Game.dataViewport,"Vel X: ", 0, 10, 65, 255, 0, 255);
    Game.putText(Game.dataViewport,std::to_string(Ship.velX), 0, 70, 65, 255, 255, 255);    

    Game.putText(Game.dataViewport,"Vel Y: ", 0, 10, 85, 0, 255,0);
    Game.putText(Game.dataViewport,std::to_string(Ship.velY), 0, 70, 85, 255, 255, 255);   

    Game.putText(Game.dataViewport,"Vel A: ", 0, 10, 105, 255, 0,0);
    Game.putText(Game.dataViewport,std::to_string(Ship.velA), 0, 70, 105, 255, 255, 255);   

    Game.putText(Game.dataViewport,"ViewX: ", 0, 10, 125, 0, 255,0);
    Game.putText(Game.dataViewport,std::to_string(Game.mainViewport.focusX), 0, 70, 125, 255, 255, 255);   

    Game.putText(Game.dataViewport,"ViewY: ", 0, 10, 145, 255, 0,0);
    Game.putText(Game.dataViewport,std::to_string(Game.mainViewport.focusY), 0, 70, 145, 255, 255, 255);   
    
    //Game.putText("Space Battle!", 1, 248, 5, 255, 255, 0);
}


/// @brief Load Vector Graphics into Object
void LoadGraphics()
{
        Ship.graphic = {
        //Body
        {0,8,-7,-10,122,122,122},
        {-7,-10,-4,-9,122,122,122},
        {-4,-9,-1,-5,122,122,122},
        {-1,-5,1,-5, 122,122,122},
        {1,-5,4,-9,122,122,122},
        {4,-9,7,-10,122,122,122},
        {7,-10,0,8,122,122,122},

        //Window
        {-1,1,-3,-4,0,0,255},
        {-3,-4,-1,-3,0,0,255},
        {-1,-3,1,-3,0,0,255},
        {1,-3,3,-4,0,0,255},
        {3,-4,1,1,0,0,255},

        //Thruster
        {-1,-6,-2,-8,255,255,0},
        {-2,-8,-2,-10,255,255,0},
        {-2,-10,2,-10,255,255,0},
        {2,-10,2,-8,255,255,0},
        {2,-8,1,-6,255,255,0}

    };
}




// Game.putText("Health:", 0, 10, 5, 255, 0, 255);
// Game.putText(std::to_string(Player.health), 0, 90, 5, 255, 255, 255);

// Game.putText("Ammo: ",0, 515, 5, 0, 255,0);
// Game.putText(std::to_string(Player.ammo), 0, 595, 5, 255, 255, 255);  

// Game.putText("Enemies: ",0, 490, 440, 255, 0,0);
// Game.putText(std::to_string(Player.numEnemyShips), 0, 595, 440, 255, 255, 255);

// Game.putText("Score: ", 0, 10, 440, 0, 0,255);
// Game.putText(std::to_string(Player.score), 0, 90, 440, 255, 255, 255);    



// void DrawLaser(int x, int y, int col)
// {
//     if(col==1) {Game.drawLine(x,y,x,y-10,LASERCOLOR_R,LASERCOLOR_G,LASERCOLOR_B);}
//     if(col==2) {Game.drawLine(x,y,x,y-10,LASERCOLOR_ENEMY_R,LASERCOLOR_ENEMY_G,LASERCOLOR_ENEMY_B);}
// }

// void DrawExplosion(int x, int y, int rad, int col)
// {
//     for(int i=0; i < EXPLOSIONPARTICLES; i++)
//     {
//         Game.drawPoint(x + Game.getRandom(rad * -1, rad), y + Game.getRandom(rad * -1, rad), 255, 255, 0);
//         //Point(x + Rando(EXPLOSIONSIZE * -1, EXPLOSIONSIZE), y + Rando(EXPLOSIONSIZE * -1, EXPLOSIONSIZE), 255, 255, 0);

//     }
//     if(col==1) Game.drawCircle(x,y,rad,255,0,0);
//     if(col==2) Game.drawCircle(x,y,rad,0,255,0);
// }


//Draw Enemies
// for(int i = 0; i < Player.numEnemyShips; i++)
// {
//     DrawEnemy(Enemy[i].posX, Enemy[i].y, 1);
// }

//Draw the lasers
// for(int i = 0; i < MAXNUMLASERS; i++)
// {
//     if(Laser[i].active)
//     {
//         DrawLaser(Laser[i].x,Laser[i].y, Laser[i].color);
//     }
// }

//Draw Explosions
// for(int i = 0; i < MAXNUMEXPLOSIONS; i++)
// {
//     if(Explosion[i].active)
//     {
//         DrawExplosion(Explosion[i].x,Explosion[i].y, Explosion[i].stage, Explosion[i].color);
//     }
// }