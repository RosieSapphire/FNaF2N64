#include "camera.h"
#include "object.h"
#include "atlas.h"
#include "util.h"
#include "sfx.h"
#include "blip.h"
#include "global.h"
#include "lights.h"
#include "mask.h"
#include <stdlib.h>

#include "toy_bonnie.h"

#define FLIP_FRAMES 11
#define CAM_TURN_MIN -576

const int buttonPos[CAM_COUNT][2] = {
	{602, 557}, {734, 558}, {602, 491},
	{737, 491}, {608, 651}, {723, 651},
	{758, 431}, {603, 420}, {915, 390},
	{847, 509}, {950, 465}, {933, 558},
};

float camFollow = 0.0f;
int camDir = 0;
float glitchTimer = 0.0f;

Object camFlip[FLIP_FRAMES];
const char *camFlipPaths[FLIP_FRAMES] = {
	"rom:/camflip00.ci8.sprite",
	"rom:/camflip01.ci8.sprite",
	"rom:/camflip02.ci8.sprite",
	"rom:/camflip03.ci8.sprite",
	"rom:/camflip04.ci8.sprite",
	"rom:/camflip05.ci8.sprite",
	"rom:/camflip06.ci8.sprite",
	"rom:/camflip07.ci8.sprite",
	"rom:/camflip08.ci8.sprite",
	"rom:/camflip09.ci8.sprite",
	"rom:/camflip10.ci8.sprite",
};

const char *party1CamPaths[4] = {
	"rom:/party_1_dark.ci8.sprite",
	"rom:/party_1_empty.ci8.sprite",
	"rom:/party_1_chica.ci8.sprite",
	"rom:/party_1_old_bonnie.ci8.sprite",
};

const char *party2CamPaths[5] = {
	"rom:/party_2_empty_dark.ci8.sprite",
	"rom:/party_2_empty_light.ci8.sprite",
	"rom:/party_2_bonnie.ci8.sprite",
	"rom:/party_2_old_chica_dark.ci8.sprite",
	"rom:/party_2_old_chica_light.ci8.sprite",
};

const char *party3CamPaths[5] = {
	"rom:/party_3_empty_dark.ci8.sprite",
	"rom:/party_3_empty_light.ci8.sprite",
	"rom:/party_3_fred_dark.ci8.sprite",
	"rom:/party_3_fred_light.ci8.sprite",
	"rom:/party_3_bonnie.ci8.sprite",
};

const char *party4CamPaths[7] = {
	"rom:/party_4_empty_dark.ci8.sprite",
	"rom:/party_4_empty_light.ci8.sprite",
	"rom:/party_4_pal.ci8.sprite",
	"rom:/party_4_chica.ci8.sprite",
	"rom:/party_4_old_chica.ci8.sprite",
	"rom:/party_4_bonnie_dark.ci8.sprite",
	"rom:/party_4_bonnie_light.ci8.sprite",
};

const char *leftVentCamPaths[6] = {
	"rom:/left_vent_dark.ci8.sprite",
	"rom:/left_vent_empty.ci8.sprite",
	"rom:/left_vent_balloon.ci8.sprite",
	"rom:/left_vent_chica.ci8.sprite",
	"rom:/left_vent_old_bonnie.ci8.sprite",
	"rom:/left_vent_endo.ci8.sprite",
};

const char *rightVentCamPaths[6] = {
	"rom:/right_vent_dark.ci8.sprite",
	"rom:/right_vent_empty.ci8.sprite",
	"rom:/right_vent_bonnie.ci8.sprite",
	"rom:/right_vent_mangle.ci8.sprite",
	"rom:/right_vent_old_chica.ci8.sprite",
};

const char *mainHallCamPaths[6] = {
	"rom:/main_hall_empty_dark.ci8.sprite",
	"rom:/main_hall_empty_light.ci8.sprite",
	"rom:/main_hall_old_bonnie.ci8.sprite",
	"rom:/main_hall_old_fred.ci8.sprite",
	"rom:/main_hall_chica_dark.ci8.sprite",
	"rom:/main_hall_chica_light.ci8.sprite",
};

const char *partsCamPaths[7] = {
	"rom:/parts_dark.ci8.sprite",
	"rom:/parts_all.ci8.sprite",
	"rom:/parts_fred.ci8.sprite",
	"rom:/parts_fred_chic.ci8.sprite",
	"rom:/parts_purple.ci8.sprite",
	"rom:/parts_fox.ci8.sprite",
	"rom:/parts_empty.ci8.sprite",
};

const char *stageCamPaths[7] = {
	"rom:/stage_all_dark.ci8.sprite",
	"rom:/stage_all_light.ci8.sprite",
	"rom:/stage_fred_chic_dark.ci8.sprite",
	"rom:/stage_fred_chic_light.ci8.sprite",
	"rom:/stage_fred_dark.ci8.sprite",
	"rom:/stage_fred_light.ci8.sprite",
	"rom:/stage_empty.ci8.sprite",
};

const char *gameAreaCamPaths[6] = {
	"rom:/game_area_bb_dark.ci8.sprite",
	"rom:/game_area_bb_light.ci8.sprite",
	"rom:/game_area_empty_dark.ci8.sprite",
	"rom:/game_area_empty_light.ci8.sprite",
	"rom:/game_area_fred_bb_light.ci8.sprite",
	"rom:/game_area_fred_light.ci8.sprite",
};

const char *prizeCornerCamPaths[6] = {
	"rom:/prize_corner_dark.ci8.sprite",
	"rom:/prize_corner_empty.ci8.sprite",
	"rom:/prize_corner_puppet0.ci8.sprite",
	"rom:/prize_corner_puppet1.ci8.sprite",
	"rom:/prize_corner_puppet2.ci8.sprite",
	"rom:/prize_corner_endo.ci8.sprite",
};

const char *kidsCoveCamPaths[3] = {
	"rom:/kids_cove_dark.ci8.sprite",
	"rom:/kids_cove_mangle.ci8.sprite",
	"rom:/kids_cove_empty.ci8.sprite",
};

const int camStateCounts[CAM_COUNT] = {
	4, 5, 5, 7, 6, 6, 6, 7, 7, 6, 6, 3
};

const char **viewPaths[CAM_COUNT] = {
	party1CamPaths, party2CamPaths, party3CamPaths, party4CamPaths,
	leftVentCamPaths, rightVentCamPaths, mainHallCamPaths, partsCamPaths,
	stageCamPaths, gameAreaCamPaths, prizeCornerCamPaths, kidsCoveCamPaths
};

enum CameraStates camSelected = CAM_09;
int camStateLast = 0;
int camState = 0;
Object views[CAM_COUNT];

static float timer = 0.0f;
bool isCameraUsing = false;
bool isCameraVisible = false;

Object map;
Atlas camNameAtlas;
rspq_block_t *mapBlock, *camNamesBlock;

Object buttons[2];
const char *buttonPaths[2] = {
	"rom:/cam_button0.ci8.sprite",
	"rom:/cam_button1.ci8.sprite",
};

void CameraFlipLoad(void)
{
	ObjectsLoad(camFlip, FLIP_FRAMES, camFlipPaths);
}

void CameraFlipUnload(void)
{
	ObjectsUnload(camFlip, FLIP_FRAMES);
}

void CameraUILoad(void)
{
	ObjectLoad(&map, "rom:/cam_map.ia4.sprite");
	ObjectsLoad(buttons, 2, buttonPaths);
	AtlasLoad(&camNameAtlas, "rom:/cam_bname_atlas.ia4.sprite", 11, 10);

	rspq_block_begin();
	ObjectDraw(map, 727, 499, 182, 152);
	mapBlock = rspq_block_end();

	rspq_block_begin();
	for(int i = 0; i < CAM_COUNT; i++)
		AtlasDraw(camNameAtlas, buttonPos[i][0],
				buttonPos[i][1], 21, 12, i);
	camNamesBlock = rspq_block_end();
}

void CameraUIUnload(void)
{
	rspq_block_free(mapBlock);
	ObjectsUnload(buttons, 2);
	AtlasUnload(&camNameAtlas);
	ObjectUnload(&map);
}

void CameraViewsUnload(bool excludeUsing)
{
	for(int i = 0; i < CAM_COUNT; i++) {
		if(excludeUsing && (i == (int)camSelected)
				&& (camStateLast == camState))
			continue;

		ObjectUnload(views + i);
	}
}

bool CameraFlipAtStart(void)
{
	int frame = (int)timer;
	return frame == 0;
}

bool CameraFlipAtEnd(void)
{
	int frame = (int)timer;
	return frame == FLIP_FRAMES;
}

bool CameraFlipAtStartOrEnd(void)
{
	return CameraFlipAtStart() || CameraFlipAtEnd();
}

void CameraFlipDraw(void)
{
	if(CameraFlipAtStartOrEnd())
		return;

	ObjectDraw(camFlip[(int)timer], 0, 0, 0, 0);
}

void CameraUIDraw(void)
{
	rdpq_set_mode_standard();
	rdpq_mode_alphacompare(true);
	rspq_block_run(mapBlock);

	/* Draw cam buttons */
	for(int i = 0; i < CAM_COUNT; i++) {
		int buttonState = ((int)camSelected == i);
		ObjectDraw(buttons[buttonState], buttonPos[i][0],
				buttonPos[i][1], 30, 20);
	}


	rspq_block_run(camNamesBlock);

	const char *camRoomNames[CAM_COUNT] = {
		"Party Room 1",
		"Party Room 2",
		"Party Room 3",
		"Party Room 4",
		"Left Air Vent",
		"Right Air Vent",
		"Main Hall",
		"Parts/Service",
		"Show Stage",
		"Game Area",
		"Prize Corner",
		"Kid's Cove",
	};

	rdpq_font_begin(RGBA16(0xFF, 0xFF, 0xFF, 0xFF));
	rdpq_font_position(172, 96);
	rdpq_font_print(pixelFont, camRoomNames[camSelected]);
	rdpq_font_end();
}

void CameraFlipUpdate(double dt, struct controller_data down)
{
	float flipSpeed = isCameraUsing ? SpeedFPS(90) : SpeedFPS(50);
	timer = Clampf(timer + dt * (isCameraUsing * 2 - 1) * flipSpeed,
			0, FLIP_FRAMES);

	if(glitchTimer) {
		mixer_ch_set_vol(SFXC_STARE, 0.6f, 0.6f);
	} else {
		mixer_ch_set_vol(SFXC_STARE, 0, 0);
	}

	if(isMaskOn)
		return;

	bool isCameraUsingLast = isCameraUsing;
	isCameraUsing ^= down.c->R && CameraFlipAtStartOrEnd();
	bool isCameraVisibleLast = isCameraVisible;
	isCameraVisible = CameraFlipAtEnd();
	mixer_ch_set_vol(SFXC_CAMERA_FLIP, 0.5f, 0.5f);

	if(isCameraVisible && !isCameraVisibleLast)
		BlipTrigger(true, 1);

	if(isCameraUsing == isCameraUsingLast)
		return;

	wav64_play(isCameraUsing ? &camUpSFX : &camDownSFX, SFXC_CAMERA_FLIP);
}

void CameraViewDraw(void)
{
	CameraViewsUnload(true);

	if(glitchTimer) {
		rdpq_set_mode_fill(RGBA16(0, 0, 0, 0xFF));
		rdpq_fill_rectangle(0, 0, 320, 240);
		CameraViewsUnload(false);
		return;
	}

	debugf("%d, %d\n", camSelected, camState);
	ObjectLoad(views + camSelected, viewPaths[camSelected][camState]);

	float camFollowReal = Clampf(camFollow, CAM_TURN_MIN, 0);
	camFollowReal *= camSelected > CAM_06;

	rdpq_set_mode_copy(false);
	ObjectDraw(views[camSelected], camFollowReal, 0, 0, 0);
}

void CameraViewUpdate(double dt, struct controller_data down)
{
	camStateLast = camState;
	bool toyBonnieInRoom = toyBonnieCam == (int)camSelected;
	bool toyBonnieAppeared = toyBonnieCamLast != toyBonnieCam &&
		((toyBonnieCamLast == (int)camSelected) || 
		(toyBonnieCam == (int)camSelected));
	bool lightOn = lightState > 0;

	glitchTimer = Clampf(glitchTimer - dt * 60, 0, 150);
	if(toyBonnieAppeared)
		glitchTimer = 50 + (rand() % 100);

	switch(camSelected) {
	case CAM_01:
		camState = lightOn;
		break;

	case CAM_02:
		if(lightOn) {
			camState = 1;
			if(toyBonnieInRoom) {
				camState = 2;
				toyBonnieStunTimer = 400;
			}
		} else {
			camState = 0;
		}
		break;

	case CAM_03:
		if(lightOn) {
			camState = 1;
			if(toyBonnieInRoom) {
				camState = 4;
				toyBonnieStunTimer = 400;
			}
		} else
			camState = 0;
		break;

	case CAM_04:
		if(lightOn) {
			camState = 1;
			if(toyBonnieInRoom) {
				camState = 6;
				toyBonnieStunTimer = 400;
			}
		} else {
			if(toyBonnieInRoom)
				camState = 5;
			else
				camState = 0;
		}
		break;

	case CAM_05:
		camState = lightOn;
		break;

	case CAM_06:
		if(lightOn) {
			camState = 1;
			if(toyBonnieInRoom) {
				camState = 2;
				toyBonnieStunTimer = 400;
			}
		} else
			camState = 0;
		break;

	case CAM_07:
		camState = lightOn;
		break;

	case CAM_08:
		camState = lightOn;
		break;

	case CAM_09:
		if(lightOn) {
			camState = 1;
			if(!toyBonnieInRoom)
				camState = 3;
		} else {
			camState = 0;
			if(!toyBonnieInRoom)
				camState = 2;
		}
		break;

	case CAM_10:
		camState = lightOn;
		break;

	case CAM_11:
		camState = lightOn;
		break;

	case CAM_12:
		camState = lightOn;
		break;

	default:
		break;
	}

	/* Update camera follow */
	if(camFollow > 120)
		camDir = 0;

	if(camFollow < -692)
		camDir = 1;

	const float camTurnSpeed = 130;
	if(camDir)
		camFollow += dt * camTurnSpeed;
	else
		camFollow -= dt * camTurnSpeed;

	if(!isCameraVisible) {
		mixer_ch_set_vol(SFXC_CAMERA_DRONE, 0, 0);
		CameraViewsUnload(false);
		return;
	}

	mixer_ch_set_vol(SFXC_CAMERA_DRONE, 0.7f, 0.7f);

	bool dirs[4] = {
		down.c->C_left, down.c->C_right, down.c->C_up, down.c->C_down,
	};

	int camSelectedNextLUT[CAM_COUNT][4] = {
		{    -1, CAM_02, CAM_03, CAM_05},
		{CAM_01, CAM_10, CAM_04, CAM_06},
		{    -1, CAM_04, CAM_08, CAM_01},
		{CAM_03, CAM_10, CAM_07, CAM_02},
		{    -1, CAM_06, CAM_01,     -1},
		{CAM_05,     -1, CAM_02,     -1},
		{CAM_08, CAM_09,     -1, CAM_04},
		{    -1, CAM_07,     -1, CAM_03},
		{CAM_07,     -1,     -1, CAM_11},
		{CAM_04, CAM_11, CAM_09, CAM_12},
		{CAM_10,     -1, CAM_09, CAM_12},
		{CAM_10,     -1, CAM_11,     -1},
	};

	for(int i = 0; i < 4; i++) {
		if(!dirs[i])
			continue;

		int newCamSelected = camSelectedNextLUT[camSelected][i];
		if((int)newCamSelected == -1)
			continue;

		camSelected = newCamSelected;
		camState = 0;
		BlipTrigger(true, 1);
		break;
	}
}
