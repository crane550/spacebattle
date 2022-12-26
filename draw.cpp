#include <math.h>
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
extern spaceobject Star[NUM_STARS];
extern spaceobject Laser[MAX_NUM_LASERS];
extern spaceobject Explosion[MAX_NUM_EXPLOSIONS];

void Draw()
{    
    Game.drawnObjects = 0;

    DrawStars();

    if(Player.inGame)
    {        
        DrawEnemys();

        DrawLasers();
        DrawCrosshairs();
        DrawShip();
        DrawExplosions();

        DrawGameText();

        DrawBorder(Game.dataViewport);
        DrawBorder(Game.mainViewport);

    }

    if(Player.inMenu)
    {       
        DrawMenuText();
    }

    if(Player.inWaitingToContinue)
    {
        // Game.putText("Game Over!", 1, 270, 200, 255, 0, 0);
        // Game.putText("(C)ontinue...", 1, 270,240,0,255,0);
    }

}

void DrawStars()
{
    //Draw the Stars
    for(int i = 0; i < NUM_STARS; i++)
    {
        Game.drawPoint(Game.mainViewport, Star[i].posX, Star[i].posY, 0, 255, 255);
    }
}

void DrawEnemys()
{
    //Draw Enemy  
    for(int e = 0; e < MAX_NUM_ENEMIES; e++)
    {
        if (Enemy[e].active)
        {
            if(inBounds(Game.mainViewport, Enemy[e]))
            {
                Game.drawSprite(Game.mainViewport,
                                Enemy[e].texture,
                                Enemy[e].posX,
                                Enemy[e].posY,
                                Enemy[e].posA);
                DrawFrame(Enemy[e], 140, 0, 0);
            }
        }
        
    }
}

void DrawLasers()
{
        for(int i = 0; i < MAX_NUM_LASERS; i++)
        {
            if(Laser[i].active)
            {
                if(inBounds(Game.mainViewport, Laser[i]))
                {
                    Game.drawLineS(Game.mainViewport,
                                Laser[i].posX,
                                Laser[i].posY,
                                Laser[i].posX + (sin(Laser[i].posA * RAD_TO_DEG) * LASER_LEN),
                                Laser[i].posY + (cos(Laser[i].posA * RAD_TO_DEG) * LASER_LEN),
                                255,0,0 );
                }
            }
        }
}

void DrawExplosions()
{
    //Draw Enemy  
    for(int e = 0; e < MAX_NUM_EXPLOSIONS; e++)
    {
        if (Explosion[e].active)
        {
            if(inBounds(Game.mainViewport, Explosion[e]))
            {
                Game.drawSprite(Game.mainViewport,
                                Explosion[e].texture,
                                Explosion[e].posX,
                                Explosion[e].posY,
                                Explosion[e].posA);
            }
        }
        
    }
}

void DrawCrosshairs()
{
    Game.drawLineS(Game.mainViewport,   Ship.posX - 50,
                                        Ship.posY,
                                        Ship.posX + 50,
                                        Ship.posY,
                                        30,30,30);
    Game.drawLineS(Game.mainViewport,   Ship.posX,
                                        Ship.posY - 50,
                                        Ship.posX,
                                        Ship.posY + 50,
                                        30,30,30);    
}

void DrawShip()
{
    Game.drawSprite(Game.mainViewport,
                    Ship.texture,
                    Ship.posX,
                    Ship.posY,
                    Ship.posA);  
}

void DrawGameText()
{
    Game.putText(0, Game.dataViewport,"X:", 0, 10, 5, 255, 0, 255);
    Game.putText(0, Game.dataViewport,std::to_string(Ship.posX), 0, 70, 5, 255, 255, 255);
    
    Game.putText(0, Game.dataViewport,"Y: ",0, 10, 25, 0, 255,0);
    Game.putText(0, Game.dataViewport,std::to_string(Ship.posY), 0, 70, 25, 255, 255, 255);  

    Game.putText(0, Game.dataViewport,"A: ",0, 10, 45, 255, 0,0);
    Game.putText(0, Game.dataViewport,std::to_string(Ship.posA), 0, 70, 45, 255, 255, 255);

    Game.putText(0, Game.dataViewport,"Vel X: ", 0, 10, 65, 255, 0, 255);
    Game.putText(0, Game.dataViewport,std::to_string(Ship.velX), 0, 70, 65, 255, 255, 255);    

    Game.putText(0, Game.dataViewport,"Vel Y: ", 0, 10, 85, 0, 255,0);
    Game.putText(0, Game.dataViewport,std::to_string(Ship.velY), 0, 70, 85, 255, 255, 255);   

    Game.putText(0, Game.dataViewport,"Vel A: ", 0, 10, 105, 255, 0,0);
    Game.putText(0, Game.dataViewport,std::to_string(Ship.velA), 0, 70, 105, 255, 255, 255);   

    Game.putText(0, Game.dataViewport,"ViewX: ", 0, 10, 125, 0, 255,0);
    Game.putText(0, Game.dataViewport,std::to_string(Game.mainViewport.focusX), 0, 70, 125, 255, 255, 255);   

    Game.putText(0, Game.dataViewport,"ViewY: ", 0, 10, 145, 255, 0,0);
    Game.putText(0, Game.dataViewport,std::to_string(Game.mainViewport.focusY), 0, 70, 145, 255, 255, 255);   

    Game.putText(0, Game.dataViewport,"Tot V: ", 0, 10, 165, 255, 0,0);
    Game.putText(0, Game.dataViewport,std::to_string(Ship.velTotal), 0, 70, 165, 255, 255, 255);   

    Game.putText(0, Game.dataViewport,"Scale: ", 0, 10, 185, 255, 0,0);
    Game.putText(0, Game.dataViewport,std::to_string(Game.mainViewport.scale), 0, 70, 185, 255, 255, 255); 

    Game.putText(0, Game.dataViewport,"D_Obj: ", 0, 10, 205, 255, 0,0);
    Game.putText(0, Game.dataViewport,std::to_string(Game.drawnObjects), 0, 70, 205, 255, 255, 255); 
    
}

void DrawMenuText()
{
    Game.putText(0, Game.mainViewport,"Space Battle!", 1, 250, 150, 255,255, 0);
    Game.putText(0, Game.mainViewport,"(N)ew Game", 1, 250, 180, 0, 255, 0);
    Game.putText(0, Game.mainViewport,"e(X)it", 1, 250, 210, 255, 0, 0);
}

void DrawBorder(viewport& vp)
{
    Game.drawLine(vp, 0, 0, vp.windowWidth, 0, 120, 120, 120);
    Game.drawLine(vp, vp.windowWidth, 0, vp.windowWidth, vp.windowHeight, 120, 120, 120);
    Game.drawLine(vp, vp.windowWidth, vp.windowHeight, 0, vp.windowHeight, 120, 120, 120);
    Game.drawLine(vp, 0,vp.windowHeight, 0, 0, 120, 120, 120);

    return;
}

void DrawFrame(spaceobject& so, int r, int g, int b)
{
    Game.drawLineS( Game.mainViewport,
                    so.posX - FRAME_PADDING,
                    so.posY + FRAME_PADDING,
                    so.posX + FRAME_PADDING,
                    so.posY + FRAME_PADDING,
                    r, b, g);
    Game.drawLineS( Game.mainViewport,
                    so.posX + FRAME_PADDING,
                    so.posY + FRAME_PADDING,
                    so.posX + FRAME_PADDING,
                    so.posY - FRAME_PADDING,
                    r, b, g);
    Game.drawLineS( Game.mainViewport,
                    so.posX + FRAME_PADDING,
                    so.posY - FRAME_PADDING,
                    so.posX - FRAME_PADDING,
                    so.posY - FRAME_PADDING,
                    r, b, g);
    Game.drawLineS( Game.mainViewport,
                    so.posX - FRAME_PADDING,
                    so.posY - FRAME_PADDING,
                    so.posX - FRAME_PADDING,
                    so.posY + FRAME_PADDING,
                    r, b, g);
    
    //string passedtext = so.callsign;
    Game.putTextS(1,Game.mainViewport, so.callsign,so.posX - 22, so.posY + 30, r,g,b);
}

//////////////////////////////////////////////////////////
//////////////////// DRAW UTILITIES //////////////////////
//////////////////////////////////////////////////////////

bool inBounds(viewport &vp, spaceobject &so)
{
    if(abs(vp.focusX - so.posX) * vp.scale < vp.windowWidthHalf + VIEWPORT_PADDING &&
       abs(vp.focusY - so.posY) * vp.scale < vp.windowHeightHalf + VIEWPORT_PADDING) return true;
    
    return false;
}

void UpdateViewport()
{
    // Scale
    Game.mainViewport.targetScale = (MAIN_VIEWPORT_MAX_SCALE) - (Ship.velTotal * .1) + Game.mainViewport.userScale;

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

    return;
}


