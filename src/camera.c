#include "camera.h"
#include "object.h"
#include "atlas.h"
#include "util.h"
#include "sfx.h"
#include "blip.h"

#define FLIP_FRAMES 11

const int buttonPos[CAM_COUNT][2] = {
	{602, 557}, {734, 558}, {602, 491},
	{737, 491}, {608, 651}, {723, 651},
	{758, 431}, {603, 420}, {915, 390},
	{847, 509}, {950, 465}, {933, 558},
};

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

const char **viewPaths[CAM_COUNT] = {
	party1CamPaths, party2CamPaths, party3CamPaths, party4CamPaths,
	leftVentCamPaths, rightVentCamPaths, mainHallCamPaths, partsCamPaths,
	stageCamPaths, gameAreaCamPaths, prizeCornerCamPaths, kidsCoveCamPaths
};

enum CameraStates camState = CAM_09;
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
		if(excludeUsing && (i == (int)camState))
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

	for(int i = 0; i < CAM_COUNT; i++) {
		int buttonState = ((int)camState == i);
		ObjectDraw(buttons[buttonState], buttonPos[i][0],
				buttonPos[i][1], 30, 20);
	}
	
	rspq_block_run(camNamesBlock);
}

void CameraFlipUpdate(double dt, struct controller_data down)
{
	float flipSpeed = isCameraUsing ? SpeedFPS(90) : SpeedFPS(50);
	timer = Clampf(timer + dt * (isCameraUsing * 2 - 1) * flipSpeed,
			0, FLIP_FRAMES);

	bool isCameraUsingLast = isCameraUsing;
	isCameraUsing ^= down.c->R && CameraFlipAtStartOrEnd();
	bool isCameraVisibleLast = isCameraVisible;
	isCameraVisible = CameraFlipAtEnd();
	mixer_ch_set_vol(SFXC_CAMERA_FLIP, 0.5f, 0.5f);

	/* Handle events for just opening and closing camera */
	if(isCameraVisible != isCameraVisibleLast) {
		if(isCameraVisible) {
			BlipTrigger(true, 1);
			mixer_ch_set_vol(SFXC_CAMERA_DRONE, 0.7f, 0.7f);
		} else {
			CameraViewsUnload(false);
			mixer_ch_set_vol(SFXC_CAMERA_DRONE, 0.0f, 0.0f);
		}
	}

	if(isCameraUsing == isCameraUsingLast)
		return;

	wav64_play(isCameraUsing ? &camUpSFX : &camDownSFX, SFXC_CAMERA_FLIP);
}

void CameraViewDraw(void)
{
	CameraViewsUnload(true);
	ObjectLoad(views + camState, viewPaths[camState][0]);
	ObjectDraw(views[camState], 0, 0, 0, 0);
}
