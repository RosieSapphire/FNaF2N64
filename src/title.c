#include "title.h"
#include "object.h"
#include "static.h"
#include "util.h"
#include "global.h"
#include "blip.h"
#include "sfx.h"
#include <stdlib.h>

#define BG_STATES 4

int bgStateRand = 0;
float bgTimer = 0.0f;
Object bgStates[BG_STATES];
rspq_block_t *titleTextBlock;
int optionsUsable = 2;
int optionCur = 0;
static bool isLoaded = false;

const char *bgStatePaths[BG_STATES] = {
	"rom:/title0.ci8.sprite",
	"rom:/title1.ci8.sprite",
	"rom:/title2.ci8.sprite",
	"rom:/title3.ci8.sprite",
};

void TitleLoad(void)
{
	if(isLoaded)
		return;

	ObjectsLoad(bgStates, BG_STATES, bgStatePaths);

	rspq_block_begin();
	rdpq_font_begin(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
	const char *title_text[] = {"Five", "Nights", "at", "Freddy's", "2"};
	for(int i = 0; i < 5; i++) {
		rdpq_font_position(VCon(90), (VCon(35) + i * 22) + 22);
		rdpq_font_print(ocrFont1, title_text[i]);
	}

	const char *option_text[] = {
		"New Game", "Continue", "6th Night", "Custom Night",
	};
	for(int i = 0; i < optionsUsable; i++) {
		rdpq_font_position(VCon(90), (VCon(512) + i * 18));
		rdpq_font_print(ocrFont2, option_text[i]);
	}
	titleTextBlock = rspq_block_end();
	mixer_ch_set_vol(SFXC_BLIP, 1, 1);
	BlipTrigger(true, 0);
	wav64_play(&titleMusic, SFXC_AMBIENCE);
	wav64_play(&staticSFX, SFXC_STATIC);
	isLoaded = true;
}

void TitleUnload(void)
{
	if(!isLoaded)
		return;
	ObjectsUnload(bgStates, BG_STATES);
	rspq_block_free(titleTextBlock);
	MixerStopEverything();
	isLoaded = false;
}

void TitleDraw(void)
{
	rdpq_set_mode_copy(false);
	int bgState = bgStateRand * (bgStateRand < 4);
	ObjectDraw(bgStates[bgState], 0, 0, 0, 0);
	rdpq_set_mode_standard();
	rdpq_font_begin(RGBA16(0xF, 0xF, 0xF, 0xF));
	rspq_block_run(titleTextBlock);
	rdpq_font_position(6, 160 + (18 * optionCur));
	rdpq_font_print(ocrFont2, ">>");
	rdpq_font_end();
	rdpq_set_mode_standard();
	rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
	StaticDraw();
	BlipDraw();
}

enum Scene TitleUpdate(float dt, struct controller_data down)
{
	/* Check if we're trying to switch scenes */
	if(down.c->start) {
		TitleUnload();
		return SCENE_MAIN_GAME;
	}

	/* Update background face glitching */
	bool bgTick;
	bgTimer = Wrapf(bgTimer + dt, 0.1f, &bgTick);
	if(bgTick)
		bgStateRand = rand() & 63;

	/* Changing menu options */
	int optionLast = optionCur;
	optionCur += down.c->down - down.c->up;
	if(optionCur != optionLast)
		BlipTrigger(false, 0);

	if(optionCur >= optionsUsable)
		optionCur = 0;

	if(optionCur < 0)
		optionCur = optionsUsable - 1;

	return SCENE_TITLE_SCREEN;
}
