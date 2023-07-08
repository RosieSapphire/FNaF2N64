#include <libdragon.h>
#include <stdlib.h>
#include <time.h>
#include "sfx.h"
#include "scene.h"
#include "object.h"
#include "perspective.h"

#include "global.h"
#include "title.h"
#include "game.h"

static void N64Init(void)
{
	srand(time(0));
	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3,
			GAMMA_NONE, ANTIALIAS_RESAMPLE);
	dfs_init(DFS_DEFAULT_LOCATION);
	controller_init();
	debug_init(DEBUG_FEATURE_ALL);
	audio_init(32000, 4);
	mixer_init(SFXC_COUNT);
	rdpq_init();
	timer_init();
}

int main(void)
{
	N64Init();
	GlobalLoad();
	PerspectiveInit();
	SFXLoad();

	enum Scene scene = SCENE_TITLE_SCREEN;

	long ticksLast = get_ticks();
	while(1) {
		uint32_t ticksNow = get_ticks();
		uint32_t ticksDiff = TICKS_DISTANCE(ticksLast, ticksNow);
		double dt = (double)ticksDiff / TICKS_PER_SECOND;
		ticksLast = ticksNow;
		// debugf("%f\n", 1.0 / dt);
		// debugf("%f\n", (double)ticksNow / TICKS_PER_SECOND);

		controller_scan();
		struct controller_data down = get_keys_down();
		struct controller_data held = get_keys_held();

		surface_t *dsp = display_get();
		rdpq_attach_clear(dsp, NULL);
		switch(scene) {
		case SCENE_TITLE_SCREEN:
			TitleLoad();
			TitleDraw();
			scene = TitleUpdate(dt, down);
			break;

		case SCENE_MAIN_GAME:
			GameLoad();
			GameDraw();
			scene = GameUpdate(dt, down, held);
			break;

		default:
			debugf("ERROR: Invalid scene accessed.\n");
			break;
		}
		rdpq_detach_show();
		GlobalUpdate(dt);
		ObjectDebug(dt);

		if(audio_can_write()) {
			short *audio_buf = audio_write_begin();
			mixer_poll(audio_buf, audio_get_buffer_length());
			audio_write_end();
		}
	}
}
