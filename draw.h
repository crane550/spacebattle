#pragma once
#include <SDL2/SDL.h>
#include "objects.h"
#include "engine.h"


void Draw();

void DrawStars();
void DrawEnemys();
void DrawLasers();
void DrawExplosions();
void DrawCrosshairs();
void DrawShip();

void DrawGameText();
void DrawMenuText();
void DrawBorder(viewport&);
void DrawFrame(spaceobject&, int, int, int);

// Draw Utilities
void UpdateViewport();
bool inBounds(viewport&, spaceobject&);


