#include "game.h"
#include "sfx.h"
#include "office.h"
#include "lights.h"
#include "fan.h"
#include "perspective.h"
#include "mask.h"
#include "camera.h"
#include "blip.h"
#include "static.h"

static bool isLoaded = false;

void GameLoad(void)
{
	if(isLoaded)
		return;
	OfficeLoad();
	LightsLoad();
	FanLoad();
	MaskLoad();
	CameraUILoad();
	CameraFlipLoad();

	wav64_play(&lightHumSFX, SFXC_LIGHT_HUM);
	wav64_play(&fanSFX, SFXC_FAN);
	wav64_play(&maskBreathSFX, SFXC_MASK_BREATH);
	wav64_play(&camDroneSFX, SFXC_CAMERA_DRONE);

	isLoaded = true;
}

void GameUnload(void)
{
	if(!isLoaded)
		return;
	OfficeUnload();
	LightsUnload();
	FanUnload();
	MaskUnload();
	CameraUIUnload();
	CameraFlipUnload();
	CameraViewsUnload(false);
	isCameraVisible = false;
	isCameraUsing = false;

	MixerStopEverything();

	isLoaded = false;
}

void GameDraw(void)
{
	if(!isCameraVisible) {
		PerspectiveBegin();
		rdpq_set_mode_copy(false);
		OfficeDraw();
		rdpq_set_mode_copy(true);
		FanDraw();
		LightsDraw();
		PerspectiveEnd();
	} else {
		CameraViewDraw();
		rdpq_set_mode_copy(false);
		rdpq_set_mode_standard();
		rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
		StaticDraw();
		CameraUIDraw();
		BlipDraw();
	}

	rdpq_set_mode_copy(true);
	MaskDraw();
	CameraFlipDraw();
}

enum Scene GameUpdate(double dt, struct controller_data down,
		struct controller_data held)
{
	if(down.c->start) {
		GameUnload();
		return SCENE_TITLE_SCREEN;
	}

	OfficeUpdate(dt, held, down);
	FanUpdate(dt);
	LightsUpdate(held);
	MaskUpdate(dt, down);
	CameraFlipUpdate(dt, down);

	return SCENE_MAIN_GAME;
}
