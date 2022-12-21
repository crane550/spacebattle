#include <math.h>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
extern spaceobject Enemy[MAX_NUM_ENEMIES];
extern spaceobject Star[NUMSTARS];


//extern spaceobject Explosion[MAXNUMEXPLOSIONS];
//extern spaceobject Enemy[MAXNUMENEMIES];
//extern spaceobject Laser[MAXNUMLASERS];
//extern spaceobject HealthAmmo[MAXNUMHEALTHAMMO];

void Draw()
{    
    Game.drawnObjects = 0;
    
    //Draw the Stars
    for(int i = 0; i < NUMSTARS; i++)
    {
        Game.drawPoint(Game.mainViewport, Star[i].posX, Star[i].posY, 0, 255, 255);
    }

    if(Player.inGame)
    {        

        //Draw Enemy  
        for(int i = 0; i < MAX_NUM_ENEMIES; i++)
        {
            if(inBounds(Game.mainViewport, Enemy[i]))
            {
                Game.drawSprite(Game.mainViewport,
                                Enemy[i].texture,
                                Enemy[i].posX,
                                Enemy[i].posY,
                                Enemy[i].posA);
            }
        }
        //Draw Ship  
        
        

        Game.drawSprite(Game.mainViewport,
                        Ship.texture,
                        Ship.posX,
                        Ship.posY,
                        Ship.posA);
        

        //Draw In Game Text
        DrawGameText();

        DrawBorder(Game.dataViewport);
        DrawBorder(Game.mainViewport);

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

bool inBounds(viewport &vp, spaceobject &so)
{
    if(abs(vp.focusX - so.posX) * vp.scale < vp.windowWidthHalf + VIEWPORT_PADDING &&
       abs(vp.focusY - so.posY) * vp.scale < vp.windowHeightHalf + VIEWPORT_PADDING) return true;
    
    return false;
}

void DrawBorder(viewport& vp)
{
    Game.drawLine(vp, 0, 0, vp.windowWidth, 0, 120, 120, 120);
    Game.drawLine(vp, vp.windowWidth, 0, vp.windowWidth, vp.windowHeight, 120, 120, 120);
    Game.drawLine(vp, vp.windowWidth, vp.windowHeight, 0, vp.windowHeight, 120, 120, 120);
    Game.drawLine(vp, 0,vp.windowHeight, 0, 0, 120, 120, 120);

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

    Game.putText(Game.dataViewport,"Tot V: ", 0, 10, 165, 255, 0,0);
    Game.putText(Game.dataViewport,std::to_string(Ship.velTotal), 0, 70, 165, 255, 255, 255);   

    Game.putText(Game.dataViewport,"Scale: ", 0, 10, 185, 255, 0,0);
    Game.putText(Game.dataViewport,std::to_string(Game.mainViewport.scale), 0, 70, 185, 255, 255, 255); 

    Game.putText(Game.dataViewport,"D_Obj: ", 0, 10, 205, 255, 0,0);
    Game.putText(Game.dataViewport,std::to_string(Game.drawnObjects), 0, 70, 205, 255, 255, 255); 
    
}

void UpdateViewport()
{
    // Scale
    Game.mainViewport.targetScale = (MAIN_VIEWPORT_MAX_SCALE) - (Ship.velTotal * .1);

    if(Game.mainViewport.scale < Game.mainViewport.targetScale) Game.mainViewport.scale += .01;
    if(Game.mainViewport.scale > Game.mainViewport.targetScale) Game.mainViewport.scale -= .006 ;
    
    if(Game.mainViewport.scale > MAIN_VIEWPORT_MAX_SCALE) Game.mainViewport.scale = MAIN_VIEWPORT_MAX_SCALE;
    if(Game.mainViewport.scale < MAIN_VIEWPORT_MIN_SCALE) Game.mainViewport.scale = MAIN_VIEWPORT_MIN_SCALE;

    // Position / Focus
    Game.mainViewport.targetX = Ship.posX;
    Game.mainViewport.targetY = Ship.posY;

    //TEMPORARY
    Game.mainViewport.focusX = Game.mainViewport.targetX;
    Game.mainViewport.focusY = Game.mainViewport.targetY;
}


