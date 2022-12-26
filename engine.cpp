#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_rwops.h>
//#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <math.h>
#include <string>

#include "engine.h"
//#include "defs.h"

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
                if(event.key.repeat) break;
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
                    case SDL_SCANCODE_O:
                        usrKeyO = true;
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
                break;

            case SDL_KEYUP:
                if(event.key.repeat) break;
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_UP:
                        usrArrowUp = false;
                        break;
                    case SDL_SCANCODE_DOWN:
                        usrArrowDown = false;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        usrArrowRight = false;
                        break;
                    case SDL_SCANCODE_LEFT:
                        usrArrowLeft = false;
                        break;
                    case SDL_SCANCODE_PAGEUP:
                        usrKeyPageUp = false;
                        break;
                    case SDL_SCANCODE_PAGEDOWN:
                        usrKeyPageDown = false;
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
    usrKeyC = false;
    usrKeyN = false;
    usrKeyX = false;
    usrKeyO = false;
    usrKeySpacebar = false;
    usrKeyPageDown = false;
    usrKeyPageUp = false;
    usrKeyEscape = false;
}

//////////////////////////////////////////////////////////
///////////////////////GRAPHICS///////////////////////////
//////////////////////////////////////////////////////////

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

// Draws a Circle
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

// Draws a Line
void spacegame::drawLine(viewport& vp, int x1, int y1, int x2, int y2, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine( renderer,
                        x1 + vp.windowX,
                        y1 + vp.windowY,
                        x2 + vp.windowX,
                        y2 + vp.windowY);
}

void spacegame::drawLineS(viewport& vp, int x1, int y1, int x2, int y2, int r, int g, int b)
{
    x1 -= vp.focusX;
    x2 -= vp.focusX;
    y1 -= vp.focusY;
    y2 -= vp.focusY;
    
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine( renderer,
                        (x1 * vp.scale) + vp.windowX + vp.windowWidthHalf,
                        (y1 * -vp.scale) + vp.windowY + vp.windowHeightHalf,
                        (x2 * vp.scale) + vp.windowX + vp.windowWidthHalf,
                        (y2 * -vp.scale) + vp.windowY + vp.windowHeightHalf);
}

// Draws a Point
void spacegame::drawPoint(viewport& vp, int x, int y, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x + vp.windowX, y + vp.windowY);
}

// Draws Text
void spacegame::putText(int font, viewport& vp, std::string saythis, int cent, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r, g, b };

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(GameFont[font], saythis.c_str(), color);
    SDL_Texture* textMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    SDL_Rect rect;
    rect.x = x + vp.windowX;
    rect.y = y + vp.windowY;
    rect.w = surfaceMessage->w;
    rect.h = surfaceMessage->h;

    if(cent){ rect.x = (vp.windowWidth - rect.w) / 2; }

    SDL_RenderCopy(renderer, textMessage, NULL, &rect); 
    
    SDL_DestroyTexture(textMessage);
    SDL_FreeSurface(surfaceMessage);
}

void spacegame::putTextS(int font, viewport& vp, std::string saythis, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    x -= vp.focusX;
    y -= vp.focusY;
    
    SDL_Color color = {r, g, b };

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(GameFont[font], saythis.c_str(), color);
    SDL_Texture* textMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    SDL_Rect rect;
    rect.x = (x * vp.scale) + vp.windowX + vp.windowWidthHalf;
    rect.y = (y * -vp.scale) + vp.windowY + vp.windowHeightHalf;
    rect.w = surfaceMessage->w; // * vp.scale;
    rect.h = surfaceMessage->h; // * vp.scale;

    SDL_RenderCopy(renderer, textMessage, NULL, &rect); 
    
    SDL_DestroyTexture(textMessage);
    SDL_FreeSurface(surfaceMessage);
}

// Draws a Sprite
void spacegame::drawSprite(viewport& vp, SDL_Texture *texture, float x, float y, float angle)
{
    x -= vp.focusX;
    y -= vp.focusY;

    x *= vp.scale;
    y *= -vp.scale;

    SDL_Rect dest;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    dest.w *= vp.scale;
    dest.h *= vp.scale;

    dest.x = x - (dest.w * 0.5) + vp.windowX + vp.windowWidthHalf;
    dest.y = y - (dest.w * 0.5) + vp.windowY + vp.windowHeightHalf;

    SDL_RenderCopyEx(renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);

    drawnObjects++;
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

    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        std::cout << "SDL_Image Initialized" << std::endl;
    }

    //Initialize SDL_mixer
    //if( Mix_OpenAudio( 48000, AUDIO_S16SYS, 2, 4096)==0)
    //if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096)==0)
    // {
    //     std::cout << "Mixer Initialized" << std::endl;   
    // }

}

void spacegame::clean()
{
    //for (int i = 0; i < ( sizeof ( GameFont ) / sizeof (TTF_Font) ); i++)
    for(auto i : GameFont)
    {
        TTF_CloseFont(i);
    }
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout << "SDL cleaned\n" << std::endl;
}

SDL_Texture *spacegame::loadTexture(char *filename)
{
	SDL_Texture *texture;

	std::cout << "Loading " << filename << std::endl;

	texture = IMG_LoadTexture(renderer, filename);

	return texture;
}

void spacegame::loadFont(int font, char *filename, int size)
{
    GameFont[font] = TTF_OpenFont(filename, size);
    if(GameFont[font])
    {
        std::cout << "Loading font: " << GameFont[font] << std::endl;
    }
    else
    {
        std::cout << "Error Loading Font " << SDL_GetError() << std::endl;
    }
}

void viewport::updateViewport()
{
    windowHeightHalf = windowHeight * 0.5;
    windowWidthHalf = windowWidth * .05;
}