#include "mask.h"
#include "object.h"
#include "util.h"
#include "sfx.h"
#include "camera.h"

#define MASK_FRAMES 9

Object maskFlip[MASK_FRAMES];
Object maskOn;
const char *maskFlipPaths[MASK_FRAMES] = {
	"rom:/mask0.ci8.sprite",
	"rom:/mask1.ci8.sprite",
	"rom:/mask2.ci8.sprite",
	"rom:/mask3.ci8.sprite",
	"rom:/mask4.ci8.sprite",
	"rom:/mask5.ci8.sprite",
	"rom:/mask6.ci8.sprite",
	"rom:/mask7.ci8.sprite",
	"rom:/mask8.ci8.sprite",
};

static float timer = 0.0f;
bool isMaskOn = false;
float maskX, maskY;

void MaskLoad(void)
{
	ObjectsLoad(maskFlip, MASK_FRAMES, maskFlipPaths);
	ObjectLoad(&maskOn, "rom:/mask_on.ci8.sprite");
}

void MaskUnload(void)
{
	ObjectsUnload(maskFlip, MASK_FRAMES);
	ObjectUnload(&maskOn);
}

bool MaskAtStart(void)
{
	int frame = (int)timer;
	return frame == 0;
}

bool MaskAtEnd(void)
{
	int frame = (int)timer;
	return frame == MASK_FRAMES;
}

bool MaskAtStartOrEnd(void)
{
	return MaskAtStart() || MaskAtEnd();
}

void MaskDraw(void)
{
	if(!MaskAtStartOrEnd()) {
		ObjectDraw(maskFlip[(int)timer], 0, 0, 0, 0);
		return;
	}

	if(!MaskAtEnd())
		return;

	ObjectDraw(maskOn, maskX, maskY, 100, 66);
}

void MaskUpdate(double dt, struct controller_data down)
{
	timer = Clampf(timer + dt * (isMaskOn * 2 - 1) * SpeedFPS(75),
			0, MASK_FRAMES);

	if(isCameraUsing)
		return;

	bool inputDown = (down.c->Z || down.c->L);
	bool isMaskOnLast = isMaskOn;
	isMaskOn ^= inputDown && MaskAtStartOrEnd();

	static float bobTimer = 0.0f;
	bobTimer += dt;
	maskX = (sinf(bobTimer) * VCon(75));
	maskY = (sinf(bobTimer * 2) * VCon(34));

	float maskVolume = 0.6f * MaskAtEnd();
	mixer_ch_set_vol(SFXC_MASK_BREATH, maskVolume, maskVolume);

	if(isMaskOn == isMaskOnLast)
		return;

	wav64_play(isMaskOn ? &maskOnSFX : &maskOffSFX, SFXC_MASK_FLIP);
}
