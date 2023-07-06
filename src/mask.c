#include "mask.h"
#include "object.h"
#include "util.h"
#include "camera.h"

#define MASK_ANIM_LEN 9

static Object flipAnim[MASK_ANIM_LEN];
Object maskOn;
float flipTimer = 0.0f;
bool isMaskOn = false;
int maskOnX, maskOnY;
float maskBobTimer = 0.0f;
static bool isLoaded = false;

static const char *flipAnimPaths[MASK_ANIM_LEN] = {
	"mask0.ci8.sprite",
	"mask1.ci8.sprite",
	"mask2.ci8.sprite",
	"mask3.ci8.sprite",
	"mask4.ci8.sprite",
	"mask5.ci8.sprite",
	"mask6.ci8.sprite",
	"mask7.ci8.sprite",
	"mask8.ci8.sprite",
};

void MaskLoad(void)
{
	if(isLoaded)
		return;
	ObjectsLoad(flipAnim, flipAnimPaths, MASK_ANIM_LEN);
	ObjectLoad(&maskOn, "mask_on.ci8.sprite");
	isLoaded = true;
}

void MaskUnload(void)
{
	if(!isLoaded)
		return;
	ObjectsUnload(flipAnim, MASK_ANIM_LEN);
	ObjectUnload(&maskOn);
	isLoaded = false;
}

void MaskDraw(void)
{
	int flipFrame = (int)flipTimer;
	bool atStart = flipFrame == 0;

	if(!isMaskOn && atStart)
		return;

	bool atEnd = flipFrame == MASK_ANIM_LEN;
	rdpq_set_mode_copy(true);
	if(!atStart && !atEnd) {
		ObjectDrawFrame(flipAnim, 0, 0, 0, 0, flipFrame,
				MASK_ANIM_LEN, flipAnimPaths, false);
		return;
	}

	if(atEnd) {
		ObjectDraw(maskOn, maskOnX, maskOnY, 100, 66);
	}
}

void MaskUpdate(float dt, struct controller_data down)
{
	int flipFrame = (int)flipTimer;
	bool atStart = flipFrame == 0;
	bool atEnd = flipFrame == MASK_ANIM_LEN;
	isMaskOn ^= (down.c->L || down.c->Z) &&
		(atStart || atEnd) && !camIsUsing;

	int maskFlipSpeed = 75;
	dt *= isMaskOn * 2 - 1;
	flipTimer = Clampf(flipTimer + dt * SpeedFPS(maskFlipSpeed),
			0, MASK_ANIM_LEN);
	if(!isMaskOn)
		return;

	maskBobTimer += dt;
	maskOnX = (sinf(maskBobTimer) * 24);
	maskOnY = (sinf(maskBobTimer * 2) * 11);
}
