#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "engine.h"
#include "loop.h"
#include "defs.h"

spacegame Game;

Uint32 frames = 0;
Uint32 startFrame;
Uint32 endFrame;

int main(int argv, char** args)
{
    std::cout << "\n\nStarting...\n\n";
    std::cout << "Space Battle!\n";
    std::cout << "Version 0.1.2\n";
    std::cout << "By Alex Crane\n\n";
    
    //Randomize Timer
    srand (static_cast <unsigned> (time_t(0)));

    // Launch Screen
    Game.init("Space Battle!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    startFrame = SDL_GetTicks();

    // Main Loop Starts Here

    GameLoop();

    // Quitting Starts Here

    endFrame = SDL_GetTicks();
    Uint32 totalTime = endFrame - startFrame;
    // std::cout << "Frames per second: " << frames / totalTime << std::endl;
    // std::cout << frames << std::endl;
    std::cout << "Total Time: " << totalTime << std::endl;

    Game.clean();

    std::cout << "Shutdown Complete....exiting" << std::endl;

    return 0;
}

