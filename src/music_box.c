#include "music_box.h"
#include "global.h"
#include "object.h"
#include "util.h"
#include "camera.h"
#include "sfx.h"

#define WIND_STATES 21
#define WIND_VALUE_MAX 2000

Object windButton[2];
const char *windButtonPaths[2] = {
	"rom:/music_box_button0.ci8.sprite",
	"rom:/music_box_button1.ci8.sprite",
};

float windDownTimer = 0.0f;
float windUpSFXTimer = 0.0f;
float windUpTimer = 0.0f;
float windCooldown = 0.0f;
int windValue;
bool isWinding = false;
float warningBlinkTimer = 0.0f;
bool warningBlinkState = false;

Object warningSmall[2];
const char *warningSmallPaths[2] = {
	"rom:/music_box_warning_small0.ci4.sprite",
	"rom:/music_box_warning_small1.ci4.sprite",
};

Object warningBig[2];
const char *warningBigPaths[2] = {
	"rom:/music_box_warning_big0.ci4.sprite",
	"rom:/music_box_warning_big1.ci4.sprite",
};

Object windStates[WIND_STATES];
const char *windStatePaths[WIND_STATES] = {
	"rom:/music_circle01.ia4.sprite",
	"rom:/music_circle02.ia4.sprite",
	"rom:/music_circle03.ia4.sprite",
	"rom:/music_circle04.ia4.sprite",
	"rom:/music_circle05.ia4.sprite",
	"rom:/music_circle06.ia4.sprite",
	"rom:/music_circle07.ia4.sprite",
	"rom:/music_circle08.ia4.sprite",
	"rom:/music_circle09.ia4.sprite",
	"rom:/music_circle10.ia4.sprite",
	"rom:/music_circle11.ia4.sprite",
	"rom:/music_circle12.ia4.sprite",
	"rom:/music_circle13.ia4.sprite",
	"rom:/music_circle14.ia4.sprite",
	"rom:/music_circle15.ia4.sprite",
	"rom:/music_circle16.ia4.sprite",
	"rom:/music_circle17.ia4.sprite",
	"rom:/music_circle18.ia4.sprite",
	"rom:/music_circle19.ia4.sprite",
	"rom:/music_circle20.ia4.sprite",
	"rom:/music_circle21.ia4.sprite",
};

rspq_block_t *windUpTextBlock;

void MusicBoxLoad(void)
{
	/* Buttons and circle */
	ObjectsLoad(windStates, WIND_STATES, windStatePaths);
	ObjectsLoad(windButton, 2, windButtonPaths);

	/* Wind up text block */
	rspq_block_begin();
	rdpq_font_begin(RGBA16(0xFF, 0xFF, 0xFF, 0xFF));
	rdpq_font_position(VCon(362), VCon(598));
	rdpq_font_print(pixelFont, "Wind Up");
	rdpq_font_position(VCon(362), VCon(624));
	rdpq_font_print(pixelFont, "Music Box");
	rdpq_font_end();
	windUpTextBlock = rspq_block_end();

	ObjectsLoad(warningSmall, 2, warningSmallPaths);
	ObjectsLoad(warningBig, 2, warningBigPaths);

	windValue = WIND_VALUE_MAX - 1;
}

void MusicBoxUnload(void)
{
	ObjectsUnload(windStates, WIND_STATES);
	ObjectsUnload(windButton, 2);
	rspq_block_free(windUpTextBlock);
	ObjectsUnload(warningSmall, 2);
	ObjectsUnload(warningBig, 2);
}

void MusicBoxUpdate(double dt, struct controller_data held)
{
	bool inDanger = windValue <= 200;
	warningBlinkTimer += dt * (inDanger ? SpeedFPS(20) : SpeedFPS(5));
	bool changeBlink;
	warningBlinkTimer = Wrapf(warningBlinkTimer, 1.0f, &changeBlink);
	if(changeBlink)
		warningBlinkState ^= 1;

	windCooldown = Clampf(windCooldown - dt * 10, 0, 10);

	bool hasTickedDown;
	windDownTimer = Wrapf(windDownTimer + dt, 0.05f, &hasTickedDown);
	if(hasTickedDown && windCooldown == 0)
		windValue -= 6;

	const float musicBoxVolumes[CAM_COUNT] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0.05f, 0.15f, 0.40f, 0.15f
	};
	float volume = musicBoxVolumes[camSelected];
	if(!isCameraVisible)
		volume = 0;
	mixer_ch_set_vol(SFXC_MUSIC_BOX, volume, volume);

	isWinding = held.c->B && isCameraVisible && camSelected == CAM_11;
	if(isWinding) {
		windCooldown = 10;
		windUpSFXTimer += dt;
		windUpTimer += dt * 60;
	}

	bool addWindValue;
	windUpTimer = Wrapf(windUpTimer, 1.0f, &addWindValue);
	windValue = Clampi(windValue + 5 * addWindValue, 0, WIND_VALUE_MAX - 1);

	bool playWindSound;
	windUpSFXTimer = Wrapf(windUpSFXTimer, 0.5f, &playWindSound);
	if(playWindSound)
		wav64_play(&windSFX, SFXC_BLIP);
}

void MusicBoxDraw(void)
{
	bool inDanger = windValue <= 200;
	bool showWarning = warningBlinkState && windValue <= 400;
	rdpq_set_mode_copy(true);
	if(!isCameraVisible) {
		if(showWarning)
			ObjectDraw(warningBig[inDanger], 842, 590, 0, 0);
		return;
	}

	if(showWarning)
		ObjectDraw(warningSmall[inDanger], 868, 448, 0, 0);

	if(camSelected != CAM_11)
		return;

	rdpq_set_mode_copy(false);
	ObjectDraw(windButton[isWinding], 435, 598, 78, 32);
	rdpq_set_mode_standard();
	rdpq_mode_alphacompare(true);

	int windIndex = ((float)windValue / WIND_VALUE_MAX) * WIND_STATES;
	ObjectDraw(windStates[windIndex], 292, 590, 0, 0);
	rspq_block_run(windUpTextBlock);
}
