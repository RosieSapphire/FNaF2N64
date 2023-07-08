#include "toy_bonnie.h"
#include <stdlib.h>
#include "camera.h"
#include "util.h"

#define MOVE_TIMER 5.0f

int toyBonnieAI = 20;
int toyBonnieCamLast = CAM_09;
int toyBonnieCam = CAM_09;
float toyBonnieStunTimer = 0.0f;
static float moveTimer = 0.0f;

enum MoveState {
	MS_NONE,
	MS_ATTEMPT,
	MS_SUCCESS,
};


static enum MoveState moveState = MS_NONE;

void ToyBonnieUpdate(double dt)
{
	if(moveState == MS_ATTEMPT && !toyBonnieStunTimer) {
		moveState = MS_SUCCESS;
	}

	toyBonnieCamLast = toyBonnieCam;
	if(moveState == MS_SUCCESS) {
		moveState = MS_NONE;
		switch(toyBonnieCam) {
		case CAM_09:
			toyBonnieCam = CAM_03;
			break;

		case CAM_03:
			toyBonnieCam = CAM_04;
			break;

		case CAM_04:
			toyBonnieCam = CAM_02;
			break;

		case CAM_02:
			toyBonnieCam = CAM_06;
			toyBonnieStunTimer = 500;
			break;

		default:
			break;
		}
		debugf("Bonnie successfully moved from %d to cam %d\n",
				toyBonnieCamLast + 1, toyBonnieCam + 1);
	}

	toyBonnieStunTimer = Clampf(toyBonnieStunTimer - dt * 60, 0, 9999);

	bool moveTimerTick;
	moveTimer = Wrapf(moveTimer + dt, MOVE_TIMER, &moveTimerTick);
	if(moveTimerTick && moveState == MS_NONE) {
		int r = (rand() % 20) + 1;
		if(r <= toyBonnieAI && !toyBonnieStunTimer) {
			debugf("Bonnie is attempting to move\n");
			moveState = MS_ATTEMPT;
		}
	}
}
