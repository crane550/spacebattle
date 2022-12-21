#pragma once
#include "objects.h"
#include "engine.h"
//#include <SDL2/SDL_image.h>

void Draw();
void DrawShip(int, int, int);
//void DrawObject(spaceobject&, viewport&);
void DrawEnemy(int, int, int);
void DrawHealthAmmo(int, int, int);
void DrawLaser(int,int,int);
void DrawExplosion(int, int, int, int);
//void LoadGraphics();
void DrawGameText();
void DrawBorder(viewport&);
void UpdateViewport();
bool inBounds(viewport&, spaceobject&);


