#include "fan.h"
#include "object.h"
#include "util.h"
#include "office.h"

#define FAN_ANIM_LEN 4

Object fanAnim[4];
float fanTimer = 0.0f;

const char *fanPaths[FAN_ANIM_LEN] = {
	"fan0.ci8.sprite",
	"fan1.ci8.sprite",
	"fan2.ci8.sprite",
	"fan3.ci8.sprite",
};

void FanDraw(void)
{
	int fanFrame = (int)fanTimer;
	ObjectDrawFrame(fanAnim, 568 + officeTurn, 766, 0, 434,
			fanFrame, FAN_ANIM_LEN, fanPaths, false);
}

void FanUpdate(float dt)
{
	fanTimer += dt * SpeedFPS(100);
	fanTimer = Wrapf(fanTimer, FAN_ANIM_LEN, NULL);
}
