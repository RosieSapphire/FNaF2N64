#ifndef UTIL_H_
#define UTIL_H_

#include <stdbool.h>

int VCon(int v);
int Clampi(int x, int min, int max);
float Clampf(float x, float min, float max);
float Wrapf(float x, float max, bool *hasWrapped);
float SpeedFPS(int percent);

#endif /* UTIL_H_ */
