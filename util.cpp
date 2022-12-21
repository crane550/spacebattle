#include <math.h>
#include "util.h"
#include "defs.h"

float getAngle(int x1, int y1, int x2, int y2)
{
	float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
	return angle >= 0 ? angle : 360 + angle;
}

float getRandom(float min, float max)
{
    float randomnum = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = randomnum * diff;
    return min + r;
}