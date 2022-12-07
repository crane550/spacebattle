#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_rwops.h>
//#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <math.h>

#include "engine.h"
#include "defs.h"

using namespace std;

//Contructor
spacegame::spacegame(){setKeysOff();}
//Desctructor
spacegame::~spacegame() {}

//Pass system events to Game
void spacegame::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
            case SDL_QUIT:
                std::cout << "SDL Quit Event Initiated" << std::endl;
                isPlaying = false;
				break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_UP:
                        usrArrowUp = true;
                        break;
                    case SDL_SCANCODE_DOWN:
                        usrArrowDown = true;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        usrArrowRight = true;
                        break;
                    case SDL_SCANCODE_LEFT:
                        usrArrowLeft = true;
                        break;
                    case SDL_SCANCODE_X:
                        usrKeyX = true;
                        break;
                    case SDL_SCANCODE_SPACE:
                        usrKeySpacebar = true;
                        break;
                    case SDL_SCANCODE_N:
                        usrKeyN = true;
                        break;
                    case SDL_SCANCODE_C:
                        usrKeyC = true;
                        break;
                    case SDL_SCANCODE_P:
                        usrKeyP = true;
                        break;
                    case SDL_SCANCODE_PAGEUP:
                        usrKeyPageUp = true;
                        break;
                    case SDL_SCANCODE_PAGEDOWN:
                        usrKeyPageDown = true;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        usrKeyEscape = true;
                        break;
                    default:
                        break;
                }

			default:
				break;
		}
	}
}
//Turn off All Used Keys
void spacegame::setKeysOff()
{
    usrArrowUp = false;
    usrArrowDown = false;
    usrArrowLeft = false;
    usrArrowRight = false;
    usrKeyN = false;
    usrKeyX = false;
    usrKeySpacebar = false;
    usrKeyPageDown = false;
    usrKeyPageUp = false;
    usrKeyEscape = false;
}

//////////////////////////////////////////////////////////
///////////////////////GRAPHICS///////////////////////////
//////////////////////////////////////////////////////////
void viewport::updateViewport()
{
    float differenceX = targetX - (focusX + (windowWidth / 2));
    //float differenceY = focusY - targetY + (windowHeight / 2);
    float differenceY = targetY - (focusY - (windowHeight / 2));
        
    if(abs(differenceX) > padding) focusX += (differenceX) * shiftSpeed;
    if(abs(differenceY) > padding) focusY += (differenceY) * shiftSpeed;

    focusX += (differenceX) * shiftSpeed;
    focusY += (differenceY) * shiftSpeed;
}
// Graphics Functions
void spacegame::renderClear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void spacegame::renderPresent()
{
    SDL_RenderPresent(renderer);
}

void spacegame::drawCircle(viewport& vp, int x, int y, int radius, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    
    int x1 = radius - 1;
    int y1 = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x1 >= y1)
    {
        SDL_RenderDrawPoint(renderer, x + x1 + vp.windowX, y + y1 + vp.windowY);
        SDL_RenderDrawPoint(renderer, x + y1 + vp.windowX, y + x1 + vp.windowY);
        SDL_RenderDrawPoint(renderer, x - y1 + vp.windowX, y + x1 + vp.windowY);
        SDL_RenderDrawPoint(renderer, x - x1 + vp.windowX, y + y1 + vp.windowY);
        SDL_RenderDrawPoint(renderer, x - x1 + vp.windowX, y - y1 + vp.windowY);
        SDL_RenderDrawPoint(renderer, x - y1 + vp.windowX, y - x1 + vp.windowY);
        SDL_RenderDrawPoint(renderer, x + y1 + vp.windowX, y - x1 + vp.windowY);
        SDL_RenderDrawPoint(renderer, x + x1 + vp.windowX, y - y1 + vp.windowY);

        if (err <= 0)
        {
            y1++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x1--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void spacegame::drawLine(viewport& vp, int x1, int y1, int x2, int y2, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine( renderer,
                        x1 + vp.windowX,
                        y1 + vp.windowY,
                        x2 + vp.windowX,
                        y2 + vp.windowY);
}
//Sets color and places a pixel
void spacegame::drawPoint(viewport& vp, int x, int y, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x + vp.windowX, y + vp.windowY);
}
//Rotates Graphic to Match Angle
//Draw Text to the Screen
void spacegame::putText(viewport& vp, std::string saythis, int cent, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r, g, b };

    // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(GameFont, saythis.c_str(), color);
    //now you can convert it into a texture
    SDL_Texture* textMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    SDL_Rect rect;
    rect.x = x + vp.windowX;
    rect.y = y + vp.windowY;
    rect.w = surfaceMessage->w;
    rect.h = surfaceMessage->h;

    if(cent){ rect.x = (WINDOW_WIDTH - rect.w) / 2; }
    
    //you put the renderer's name first, the Message, the crop size(you can ignore this
    //if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture 
    SDL_RenderCopy(renderer, textMessage, NULL, &rect); 
    
    SDL_DestroyTexture(textMessage);
    SDL_FreeSurface(surfaceMessage);
}

// Init and Shutdown
void spacegame::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags=0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "SDL Initialized" << std::endl;
    }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(window)
    {
        std::cout << "Window created" << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 255);
        std::cout << "Renderer created" << std::endl;
    }
    isPlaying = true;

    if(TTF_Init()==0)
    {
        std::cout << "TTF Initialized" << std::endl;
    }

    //Initialize SDL_mixer
    //if( Mix_OpenAudio( 48000, AUDIO_S16SYS, 2, 4096)==0)
    //if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096)==0)
    // {
    //     std::cout << "Mixer Initialized" << std::endl;   
    // }

    // sndLaser = Mix_LoadWAV("sounds/FriendlyLaser.wav");
    // sndEnemyLaser = Mix_LoadWAV("sounds/EnemyLaser.wav");
    // sndBeingDestroyed = Mix_LoadWAV("sounds/BeingDestroyed.wav");
    // sndPowerUp = Mix_LoadWAV("sounds/Powerup.wav");
    // sndGameStart = Mix_LoadWAV("sounds/GameStart.wav");
    // sndEnemiesReleased = Mix_LoadWAV("sounds/EnemiesReleased.wav");
    // sndTakeDamage = Mix_LoadWAV("sounds/TakeDamage.wav");
    // sndKillEnemy = Mix_LoadWAV("sounds/KillEnemy.wav");
    // sndKillHealth = Mix_LoadWAV("sounds/KillHealth.wav");

    // if(sndLaser==NULL) std::cout << "Friendly Not OK" << std::endl;   
    // if(sndEnemyLaser==NULL) std::cout << "Enemy Not OK" << std::endl;   

    GameFont = TTF_OpenFont("fonts/DOS.ttf", DEFFONTSIZE);
    if(GameFont)
    {
        std::cout << "Loading font: " << GameFont << std::endl;
    }
    else
    {
        std::cout << "Error Loading Font " << SDL_GetError() << std::endl;
    }

}

void spacegame::clean()
{
    TTF_CloseFont(GameFont);
    
    //Close Sounds
    // Mix_FreeChunk(sndLaser);
    // Mix_FreeChunk(sndEnemyLaser);
    // Mix_FreeChunk(sndBeingDestroyed);
    // Mix_FreeChunk(sndPowerUp);
    // Mix_FreeChunk(sndGameStart);
    // Mix_FreeChunk(sndEnemiesReleased);
    // Mix_FreeChunk(sndTakeDamage);
    // Mix_FreeChunk(sndKillEnemy);
    // Mix_FreeChunk(sndKillHealth);
    //Mix_CloseAudio();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "SDL cleaned\n" << std::endl;
}

float spacegame::getRandom(float min, float max)
{
    float randomnum = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = randomnum * diff;
    return min + r;
}

void spacegame::playSound(int sound)
{
//     switch(sound)
//     {
//         case 1:
//             //Mix_PlayChannel( -1, sndLaser, 0 );
//             break;
//         case 2:
//             //Mix_PlayChannel( -1, sndEnemyLaser, 0 );
//             break;
//         case 3:
//             //Mix_PlayChannel( -1, sndGameStart, 0 );
//             break;
//         case 4:
//             //Mix_PlayChannel(-1, sndBeingDestroyed, 0);
//             break;
//         case 5:
//             //Mix_PlayChannel(-1, sndPowerUp, 0);
//             break;
//         case 6:
//             //Mix_PlayChannel(-1, sndEnemiesReleased, 0);
//             break;
//         case 7:
//             //Mix_PlayChannel(-1, sndTakeDamage, 0);
//             break;
//         case 8:
//             //Mix_PlayChannel(-1, sndKillEnemy, 0);
//             break;
//         case 9:
//             //Mix_PlayChannel(-1, sndKillHealth, 0);
//             break;            
//     }
}

void spacegame::writeHighScore(int score)
{
    // SDL_RWops *scorefile = SDL_RWFromFile("highscore.dat","w");

    // //score = 8675309;

    // char charscore[8];

    // sprintf(charscore, "%d", score);

    // SDL_RWwrite(scorefile, charscore, 1, 7);

    // SDL_RWclose(scorefile);

}

// int spacegame::readHighScore()
// {
//     //std::cout << "Opening high score file...";
//     // SDL_RWops *scorefile = SDL_RWFromFile("highscore.dat","rb");
    
//     // char readscore[8];

//     // SDL_RWread(scorefile,readscore,16,256/16);
//     // SDL_RWclose(scorefile);

//     //int score;
//     // sscanf(readscore, "%d", &score);

//     // std::cout << readscore << std::endl;

//     //return score;
// }

// What is this??
// void spacegame::update()
// {
//     cnt++;
// }
