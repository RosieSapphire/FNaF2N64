#include "fan.h"
#include "office.h"
#include "object.h"
#include "util.h"

#define FAN_FRAMES 4

Object fanAnim[FAN_FRAMES];
const char *fanAnimPaths[FAN_FRAMES] = {
	"rom:/fan0.ci8.sprite",
	"rom:/fan1.ci8.sprite",
	"rom:/fan2.ci8.sprite",
	"rom:/fan3.ci8.sprite",
};

static float timer = 0.0f;

void FanLoad(void)
{
	ObjectsLoad(fanAnim, FAN_FRAMES, fanAnimPaths);
}

void FanUnload(void)
{
	ObjectsUnload(fanAnim, FAN_FRAMES);
}

void FanDraw(void)
{
	ObjectDraw(fanAnim[(int)timer], 568 + officeTurn, 766, 0, 434);
}

void FanUpdate(double dt)
{
	timer = Wrapf(timer + dt * SpeedFPS(100), FAN_FRAMES, NULL);
}
