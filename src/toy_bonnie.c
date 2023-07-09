#include "toy_bonnie.h"
#include <stdlib.h>
#include "camera.h"
#include "util.h"
#include "object.h"
#include "sfx.h"

#define MOVE_TIMER 5.0f
#define JUMPSCARE_FRAMES 13

int toyBonnieAI = 20;
int toyBonnieCamLast = CAM_09;
int toyBonnieCam = CAM_09;
float toyBonnieStunTimer = 0.0f;
static float moveTimer = 0.0f;
bool attack = false;
bool playScare = false;

float jumpscareTimer = 0.0f;
Object jumpscareFrames[JUMPSCARE_FRAMES];
const char *jumpscareFramePaths[JUMPSCARE_FRAMES] = {
	"rom:/toy_bonnie_scare00.ci8.sprite",
	"rom:/toy_bonnie_scare01.ci8.sprite",
	"rom:/toy_bonnie_scare02.ci8.sprite",
	"rom:/toy_bonnie_scare03.ci8.sprite",
	"rom:/toy_bonnie_scare04.ci8.sprite",
	"rom:/toy_bonnie_scare05.ci8.sprite",
	"rom:/toy_bonnie_scare06.ci8.sprite",
	"rom:/toy_bonnie_scare07.ci8.sprite",
	"rom:/toy_bonnie_scare08.ci8.sprite",
	"rom:/toy_bonnie_scare09.ci8.sprite",
	"rom:/toy_bonnie_scare10.ci8.sprite",
	"rom:/toy_bonnie_scare11.ci8.sprite",
	"rom:/toy_bonnie_scare12.ci8.sprite",
};

enum MoveState {
	MS_NONE,
	MS_ATTEMPT,
	MS_SUCCESS,
};

#define IN_OFFICE    CAM_COUNT
#define YOURE_FUCKED (IN_OFFICE + 1)

static enum MoveState moveState = MS_NONE;

void ToyBonnieScareLoad(void)
{
	ObjectsLoad(jumpscareFrames, JUMPSCARE_FRAMES, jumpscareFramePaths);
}

void ToyBonnieScareUnload(void)
{
	ObjectsUnload(jumpscareFrames, JUMPSCARE_FRAMES);
}

void ToyBonnieUpdate(double dt)
{
	if(moveState == MS_ATTEMPT && !toyBonnieStunTimer) {
		moveState = MS_SUCCESS;
	}

	int moveToLUT[CAM_COUNT + 2] = {
		-1, CAM_06, CAM_04, CAM_02, -1,
		IN_OFFICE, -1, -1, CAM_03, -1, -1, -1,
		YOURE_FUCKED, YOURE_FUCKED,
	};

	toyBonnieCamLast = toyBonnieCam;
	if(moveState == MS_SUCCESS) {
		moveState = MS_NONE;
		toyBonnieCam = moveToLUT[toyBonnieCam];
		if(toyBonnieCam == CAM_06)
			toyBonnieStunTimer = 500;

		if(toyBonnieCam == IN_OFFICE)
			toyBonnieStunTimer = 1000 - 700;

		if(toyBonnieCam == YOURE_FUCKED)
			attack = true;

		debugf("Bonnie successfully moved from %d to cam %d\n",
				toyBonnieCamLast + 1, toyBonnieCam + 1);
	}

	if(attack && !isCameraVisible && isCameraVisibleLast) {
		playScare = true;
		mixer_ch_set_vol(SFXC_AMBIENCE, 1, 1);
		wav64_play(&jumpscareSFX, SFXC_AMBIENCE);
	}

	if(playScare)
		jumpscareTimer = Clampf(jumpscareTimer + dt * SpeedFPS(50),
						0, JUMPSCARE_FRAMES);

	toyBonnieStunTimer = Clampf(toyBonnieStunTimer - dt * 60, 0, 9999);
	debugf("%f\n", toyBonnieStunTimer);

	bool moveTimerTick;
	moveTimer = Wrapf(moveTimer + dt, MOVE_TIMER, &moveTimerTick);
	if(moveTimerTick && moveState == MS_NONE) {
		int r = (rand() % 20) + 1;
		if(r <= toyBonnieAI && !toyBonnieStunTimer) {
			debugf("Bonnie is attempting to move\n");
			moveState = MS_ATTEMPT;
		}
	}

	if(!attack)
		return;

}

void ToyBonnieScareDraw(void)
{
	if(!playScare)
		return;
	rdpq_set_mode_copy(true);
	ObjectDraw(jumpscareFrames[(int)jumpscareTimer], 0, 0, 0, 0);
}
