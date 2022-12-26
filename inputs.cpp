#include "engine.h"
#include "objects.h"

extern spaceplayer Player;
extern spacegame Game;
extern spaceobject Ship;

void ProcessInputs()
{
    if(Game.usrArrowUp)
    {
        Ship.impFB += Ship.impFlevel;
        //Game.usrArrowUp = false;
    }

    if(Game.usrArrowDown)
    {
        Ship.impFB -= Ship.impBlevel;
        //Game.usrArrowDown = false;
    }

    if(Game.usrArrowLeft)
    {
        Ship.impA -= Ship.impAlevel;
        //Game.usrArrowLeft = false;
    }

    if(Game.usrArrowRight)
    {
        Ship.impA += Ship.impAlevel;
        //Game.usrArrowRight = false;
    }

    if(Game.usrKeyPageDown)
    {
        Ship.impLR -= Ship.impLlevel;
        //Game.usrKeyPageDown = false;
    }

    if(Game.usrKeyPageUp)
    {
        Ship.impLR += Ship.impRlevel;
        //Game.usrKeyPageUp = false;
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

    if(Game.usrKeyN)
    {
        //Game.usrKeyN = false;
    }
    
    if(Game.usrKeyP)
    {
        Game.usrKeyP = false;
        Game.mainViewport.userScale += 1;
    }

    if(Game.usrKeyO)
    {
        Game.usrKeyO = false;
        Game.mainViewport.userScale -= 1;
    }
}