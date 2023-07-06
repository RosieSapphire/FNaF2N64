#include <libdragon.h>
#include "main_game.h"
#include "sfx.h"
#include "scene.h"
#include "object.h"
#include "perspective.h"

static void N64Init(void)
{
	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3,
			GAMMA_NONE, ANTIALIAS_RESAMPLE);
	dfs_init(DFS_DEFAULT_LOCATION);
	rdpq_init();
	controller_init();
	debug_init(DEBUG_FEATURE_ALL);
	audio_init(32000, 4);
	mixer_init(SFXC_COUNT);
}

int main(void)
{
	N64Init();
	PerspectiveInit();

	enum Scene scene = SCENE_MAIN_GAME;
	timer_init();
	long ticksLast = get_ticks();
	while(1) {
		long ticksNow = get_ticks();
		float dt = (float)TICKS_DISTANCE(ticksLast, ticksNow) /
			TICKS_PER_SECOND;
		ticksLast = ticksNow;
		debugf("%lf\n", 1.0 / dt);

		controller_scan();
		struct controller_data held = get_keys_held();
		struct controller_data down = get_keys_down();

		surface_t *dsp = display_get();
		rdpq_attach_clear(dsp, NULL);
		switch(scene) {
		case SCENE_TITLE_SCREEN:
			break;

		case SCENE_MAIN_GAME:
			MainGameDraw();
			MainGameUpdate(dt, held, down);
			break;

		default:
			break;
		}
		rdpq_detach_show();

		ObjectsDebugLoaded((float)ticksNow / TICKS_PER_SECOND);
	};
}
