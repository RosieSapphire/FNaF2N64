#include "blip.h"
#include <libdragon.h>
#include "util.h"
#include "sfx.h"

#define FRAME_MAX 5

static float timer = 0.0f;
rspq_block_t *blocks[FRAME_MAX];

void BlipLoad(void)
{
	int numCoords[FRAME_MAX] = {3, 2, 3, 2, 1};
	int coords[][2] = {
		{10, 87}, {111, 152}, {201, 240},
		{14, 31}, {126, 213},
		{14, 101}, {132, 149}, {168, 210},
		{24, 111}, {163, 210},
		{75, 91},
	};

	int totalCoords = 0;
	for(int i = 0; i < FRAME_MAX; i++) {
		rspq_block_begin();
		for(int j = 0; j < numCoords[i]; j++) {
			int k = totalCoords + j;
			rdpq_fill_rectangle(0, coords[k][0], 320, coords[k][1]);
		}
		totalCoords += numCoords[i];
		blocks[i] = rspq_block_end();
	}
}

void BlipDraw(void)
{
	int frame = (int)timer;
	if(frame >= FRAME_MAX)
		return;
	rdpq_set_mode_fill(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
	rspq_block_run(blocks[frame]);
}

void BlipUpdate(float dt)
{
	timer = Clampf(timer + dt * SpeedFPS(50), 0, FRAME_MAX);
}

void BlipTrigger(bool visual, int which)
{
	if(visual)
		timer = 0;

	wav64_play(which ? &blipSFX2 : &blipSFX1, SFXC_BLIP);
}
