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
        int WindowWidthHalf;
        int windowX;
        int windowY;

        float focusX;
        float focusY;

        float targetX;
        float targetY;

        float shiftSpeed;
        int padding;
        
        float scale;
        float target_scale;

        void updateViewport();

    private:

};

class spacegame
{
    public:
        spacegame();
        ~spacegame();

        bool usrArrowUp;
        bool usrArrowDown;
        bool usrArrowLeft;
        bool usrArrowRight;
        bool usrKeySpacebar;
        bool usrKeyN;
        bool usrKeyX;
        bool usrKeyC;
        bool usrKeyP;
        bool usrKeyPageUp;
        bool usrKeyPageDown;
        bool usrKeyEscape;

        bool isPlaying;

        float viewScale;

        void init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);

        void handleEvents();
        void update();
        void setKeysOff();
        
        void renderClear();
        void renderPresent();
        void clean();

        float getRandom(float min, float max);

        int readHighScore();
        void writeHighScore(int score);

        void playSound(int sound);

        viewport dataViewport;
        viewport mainViewport;



        TTF_Font * GameFont;

        void putText(viewport& vp, std::string saythis, int cent, int x, int y, Uint8 r, Uint8 g, Uint8 b);
        void drawCircle(viewport& vp, int x, int y, int radius, int r, int g, int b);
        void drawLine(viewport& vp, int x1, int y1, int x2, int y2, int r, int g, int b);
        void drawPoint(viewport& vp, int x, int y, int r, int g, int b);





 
    private:

        int cnt;

        SDL_Window *window;
        SDL_Renderer *renderer;

};


#endif