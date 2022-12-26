#pragma once
#ifndef engine_h
#define engine_h

#include <iostream>
#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

class viewport
{
    
    public:

        int windowHeight;
        int windowHeightHalf;
        int windowWidth;
        int windowWidthHalf;
        int windowX;
        int windowY;

        float focusX;
        float focusY;

        float targetX;
        float targetY;

        float shiftSpeed;
        int padding;
        
        float scale;
        float targetScale;
        float userScale;

        void updateViewport();

    private:

};

class spacegame
{
    public:
        spacegame();
        ~spacegame();

        void handleEvents();
        void setKeysOff();
        bool usrArrowUp;
        bool usrArrowDown;
        bool usrArrowLeft;
        bool usrArrowRight;
        bool usrKeySpacebar;
        bool usrKeyN;
        bool usrKeyX;
        bool usrKeyC;
        bool usrKeyP;
        bool usrKeyO;
        bool usrKeyPageUp;
        bool usrKeyPageDown;
        bool usrKeyEscape;

        bool isPlaying;

        void init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
        void clean();


        //void update();

        
        void renderClear();
        void renderPresent();


        //void playSound(int sound);

        viewport dataViewport;
        viewport mainViewport;

        // This shouldn't be here...or should it?
        TTF_Font * GameFont[2];

        SDL_Texture *loadTexture(char *filename);
        //void loadFont(int font, char *filename, int size);
        void loadFont(int font, char *filename, int size);

        void putText(int font, viewport& vp, std::string saythis, int cent, int x, int y, Uint8 r, Uint8 g, Uint8 b);
        void putTextS(int font, viewport& vp, std::string saythis, int x, int y, Uint8 r, Uint8 g, Uint8 b);
        void drawCircle(viewport& vp, int x, int y, int radius, int r, int g, int b);
        void drawLine(viewport& vp, int x1, int y1, int x2, int y2, int r, int g, int b);
        void drawLineS(viewport& vp, int x1, int y1, int x2, int y2, int r, int g, int b);
        void drawPoint(viewport& vp, int x, int y, int r, int g, int b);
        void drawSprite(viewport& vp, SDL_Texture *texture, float x, float y, float angle);
        //void drawSprite(viewport& vp, spaceobject& so);
        int drawnObjects;
 
    private:

        int cnt;

        SDL_Window *window;
        SDL_Renderer *renderer;

};


#endif