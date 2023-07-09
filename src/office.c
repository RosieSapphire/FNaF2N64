#include "office.h"
#include "object.h"
#include "util.h"
#include "lights.h"
#include "sfx.h"
#include "mask.h"
#include "camera.h"
#include "toy_bonnie.h"

#define ROOM_STATES 5
#define ROOM_TURN_SPEED 15
#define ROOM_TURN_NOSE_HONK -143
#define ROOM_TURN_MIN -576
#define FAN_ANIM_LEN 4

float officeTurn = ROOM_TURN_MIN >> 1;

Object roomStates[ROOM_STATES];
const char *roomStatePaths[ROOM_STATES] = {
	"rom:/room_none.ci8.sprite",
	"rom:/room_left_none.ci8.sprite",
	"rom:/room_center_none.ci8.sprite",
	"rom:/room_right_none.ci8.sprite",
	"rom:/room_right_bonnie.ci8.sprite",
};

void OfficeLoad(void)
{
	ObjectsLoad(roomStates, ROOM_STATES, roomStatePaths);
}

void OfficeUnload(void)
{
	ObjectsUnload(roomStates, ROOM_STATES);
}

void OfficeDraw(void)
{
	int roomState = lightState;
	if(toyBonnieCam == CAM_COUNT && lightState == LIGHT_RIGHT)
		roomState = 4;

	ObjectDraw(roomStates[roomState], officeTurn, 0, 0, 0);
}

void OfficeUpdate(double dt, struct controller_data held,
		struct controller_data down)
{
	if(isCameraVisible)
		return;

	int turnInput = -held.c->x + (held.c->left - held.c->right) * 85;
	officeTurn = Clampf(officeTurn + turnInput *
			dt * ROOM_TURN_SPEED, ROOM_TURN_MIN, 0);

	if(down.c->C_left && officeTurn >= ROOM_TURN_NOSE_HONK &&
			!isMaskOn)
		wav64_play(&noseHonkSFX, SFXC_BLIP);
}
