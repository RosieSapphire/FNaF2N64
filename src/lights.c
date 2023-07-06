#include "lights.h"
#include "object.h"
#include "mask.h"
#include "office.h"
#include "camera.h"

#define ROOM_TURN_LEFT_LIGHT -102
#define ROOM_TURN_RIGHT_LIGHT -467

Object left[2], right[2];

enum LightState lightState = LIGHT_NONE;

const char *leftPaths[2] = {
	"light_left_off.ci8.sprite",
	"light_left_on.ci8.sprite",
};

const char *rightPaths[2] = {
	"light_right_off.ci8.sprite",
	"light_right_on.ci8.sprite",
};

void LightsDraw(void)
{
	rdpq_set_mode_copy(true);
	ObjectDrawFrame(left, 147 + officeTurn, 429, 28, 42,
			lightState == LIGHT_LEFT, 2, leftPaths, false);
	ObjectDrawFrame(right, 1444 + officeTurn, 427, 29, 42,
			lightState == LIGHT_RIGHT, 2, rightPaths, false);
}

void LightsUpdate(struct controller_data held)
{
	lightState = LIGHT_NONE;
	if(isMaskOn || camIsVisible)
		return;

	bool turnedLeft = officeTurn > ROOM_TURN_LEFT_LIGHT;
	bool turnedRight = officeTurn < ROOM_TURN_RIGHT_LIGHT;

	if(held.c->B) {
		if(turnedLeft)
			lightState = LIGHT_LEFT;

		if(turnedRight)
			lightState = LIGHT_RIGHT;
	}

	if(held.c->A && !turnedLeft && !turnedRight)
		lightState = LIGHT_CENTER;
}
