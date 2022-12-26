#include <math.h>
#include <iostream>
#include "util.h"
#include "defs.h"
#include "objects.h"


float getAngle(int x1, int y1, int x2, int y2)
{
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (DEG_TO_RAD);
	return angle >= 0 ? angle : 360 + angle;
}

float getRandom(float min, float max)
{
    float randomnum = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = randomnum * diff;
    return min + r;
}

bool checkHypCollision(spaceobject &o1, spaceobject &o2)
{
    float distSquared = (o1.posX - o2.posX) * (o1.posX - o2.posX) + (o1.posY - o2.posY) * (o1.posY - o2.posY);
    float radsSquared = (o1.width * o1.width) + (o2.width * o2.width);

    if (radsSquared > distSquared)
    {
        return true;
    }

    return false;
    
}

float getDistSquared(spaceobject &o1, spaceobject &o2)
{
    return 0;
}

