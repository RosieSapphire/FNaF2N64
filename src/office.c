#include "office.h"
#include "object.h"
#include "util.h"
#include "lights.h"
#include "mask.h"
#include "perspective.h"
#include "fan.h"
#include "camera.h"

#define ROOM_STATE_COUNT 4
#define ROOM_TURN_MIN -576
#define TURN_SPEED 1536

Object officeStates[ROOM_STATE_COUNT];
float officeTurn = ROOM_TURN_MIN >> 1;

const char *officeStatePaths[ROOM_STATE_COUNT] = {
	"room_none.ci8.sprite",
	"room_left_none.ci8.sprite",
	"room_center_none.ci8.sprite",
	"room_right_none.ci8.sprite",
};

void OfficeDraw(void)
{
	if(camIsVisible)
		return;

	PerspectiveBegin();
	rdpq_set_mode_copy(false);
	ObjectDrawFrame(officeStates, officeTurn, 0, 0, 0, lightState,
			ROOM_STATE_COUNT, officeStatePaths, false);
	LightsDraw();
	FanDraw();
	PerspectiveEnd();
	MaskLoad();
	MaskDraw();
	CameraLoad();
	CameraFlipDraw();
}

void OfficeUpdate(float dt, struct controller_data held,
		struct controller_data down)
{
	LightsUpdate(held);
	MaskUpdate(dt, down);
	CameraFlipUpdate(dt, down);
	FanUpdate(dt);

	if(camIsVisible)
		return;

	int officeTurnInput = (held.c->right - held.c->left) + held.c->x;
	float turnDir = (float)officeTurnInput / 85.0f;
	officeTurn -= turnDir * dt * TURN_SPEED;
	officeTurn = Clampf(officeTurn, ROOM_TURN_MIN, 0);
}
