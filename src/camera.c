#include <libdragon.h>
#include "object.h"
#include "util.h"
#include <stdint.h>

#define FLIP_ANIM_LEN 11

static Object flipAnim[FLIP_ANIM_LEN];
static float flipTimer = 0.0f;
static bool isLoaded = false;
bool camIsUsing = false;
bool camIsVisible = false;

static const char *flipAnimPaths[FLIP_ANIM_LEN] = {
	"camflip00.ci8.sprite",
	"camflip01.ci8.sprite",
	"camflip02.ci8.sprite",
	"camflip03.ci8.sprite",
	"camflip04.ci8.sprite",
	"camflip05.ci8.sprite",
	"camflip06.ci8.sprite",
	"camflip07.ci8.sprite",
	"camflip08.ci8.sprite",
	"camflip09.ci8.sprite",
	"camflip10.ci8.sprite",
};

void CameraFlipLoad(void)
{
	if(isLoaded)
		return;
	ObjectsLoad(flipAnim, flipAnimPaths, FLIP_ANIM_LEN);
	isLoaded = true;
}

void CameraFlipUnload(void)
{
	if(!isLoaded)
		return;
	ObjectsUnload(flipAnim, FLIP_ANIM_LEN);
	isLoaded = false;
}

void CameraFlipDraw(void)
{
	int flipFrame = (int)flipTimer;
	if(flipFrame == 0 || flipFrame == FLIP_ANIM_LEN)
		return;

	rdpq_set_mode_copy(true);
	ObjectDrawFrame(flipAnim, 0, 0, 0, 0, flipFrame, FLIP_ANIM_LEN,
			flipAnimPaths, false);
}

void CameraFlipUpdate(float dt, struct controller_data down)
{
	int flipFrame = (int)flipTimer;
	bool atStart = flipFrame == 0;
	bool atEnd = flipFrame == FLIP_ANIM_LEN;
	camIsUsing ^= down.c->R && (atStart || atEnd);
	camIsVisible = atEnd;

	if(camIsUsing)
		flipTimer += dt * SpeedFPS(90);
	else
		flipTimer -= dt * SpeedFPS(50);

	flipTimer = Clampf(flipTimer, 0, FLIP_ANIM_LEN);
}
