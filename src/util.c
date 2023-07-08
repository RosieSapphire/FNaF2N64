#include "util.h"
#include <math.h>

int VCon(int v)
{
	return (int)ceilf((float)v * 0.3125f);
}

int Clampi(int x, int min, int max)
{
	if(x < min)
		return min;

	if(x > max)
		return max;

	return x;
}

float Clampf(float x, float min, float max)
{
	if(x < min)
		return min;

	if(x > max)
		return max;

	return x;
}

float Wrapf(float x, float max, bool *hasWrapped)
{
	bool wrapped = false;
	while(x >= max) {
		float diff = x - max;
		x = diff;
		wrapped = true;
	}

	if(hasWrapped)
		*hasWrapped = wrapped;

	return x;
}

float SpeedFPS(int percent)
{
	return ((float)percent * 0.01f) * 60.0f;
}
