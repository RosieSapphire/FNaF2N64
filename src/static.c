#include "static.h"
#include "object.h"
#include "util.h"
#include <stdlib.h>

#define STATIC_FRAMES 6

Object frames[STATIC_FRAMES];
float timer = 0.0f;
int frame = 0;

const char *staticPaths[STATIC_FRAMES] = {
	"rom:/static0.i8.sprite",
	"rom:/static1.i8.sprite",
	"rom:/static2.i8.sprite",
	"rom:/static3.i8.sprite",
	"rom:/static4.i8.sprite",
	"rom:/static5.i8.sprite",
};

void StaticLoad(void)
{
	ObjectsLoad(frames, STATIC_FRAMES, staticPaths);
}

void StaticDraw(void)
{
	ObjectDraw(frames[frame], 0, 0, 0, 0);
}

void StaticUpdate(float dt)
{
	timer += dt * SpeedFPS(99);
	bool updateFrame;
	timer = Wrapf(timer, 1, &updateFrame);

	int frame_last = frame;
	if(!updateFrame)
		return;

	while(frame == frame_last)
		frame = rand() % STATIC_FRAMES;
}
