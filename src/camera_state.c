#include "camera_state.h"
#include "camera.h"

typedef struct {
	const char *path;
	int state;
} CameraState;

const int camStateCounts[CAM_COUNT] = {
	2, 4, 4, 4, 2, 4, 2, 2, 4, 4
};

CameraState party1States[] = {
	{"rom:/party_1_dark.ci8.sprite",  CS_LIGHTS_OFF},
	{"rom:/party_1_empty.ci8.sprite", CS_LIGHTS_ON},
};

CameraState party2States[] = {
	{"rom:/party_2_empty_dark.ci8.sprite",                  CS_LIGHTS_OFF},
	{"rom:/party_2_empty_light.ci8.sprite",                  CS_LIGHTS_ON},
	{"rom:/party_2_empty_dark.ci8.sprite",  CS_LIGHTS_OFF | CS_TOY_BONNIE},
	{"rom:/party_2_bonnie.ci8.sprite",       CS_LIGHTS_ON | CS_TOY_BONNIE},
};

CameraState party3States[] = {
	{"rom:/party_3_empty_dark.ci8.sprite",                  CS_LIGHTS_OFF},
	{"rom:/party_3_empty_light.ci8.sprite",                  CS_LIGHTS_ON},
	{"rom:/party_3_empty_dark.ci8.sprite",  CS_LIGHTS_OFF | CS_TOY_BONNIE},
	{"rom:/party_3_bonnie.ci8.sprite",       CS_LIGHTS_ON | CS_TOY_BONNIE},
};

CameraState party4States[] = {
	{"rom:/party_4_empty_dark.ci8.sprite",                   CS_LIGHTS_OFF},
	{"rom:/party_4_empty_light.ci8.sprite",                   CS_LIGHTS_ON},
	{"rom:/party_4_bonnie_dark.ci8.sprite",  CS_LIGHTS_OFF | CS_TOY_BONNIE},
	{"rom:/party_4_bonnie_light.ci8.sprite",  CS_LIGHTS_ON | CS_TOY_BONNIE},
};

CameraState leftVentStates[] = {
	{"rom:/left_vent_dark.ci8.sprite", CS_LIGHTS_OFF},
	{"rom:/left_vent_empty.ci8.sprite", CS_LIGHTS_ON},
};

CameraState rightVentStates[] = {
	{"rom:/right_vent_dark.ci8.sprite",                  CS_LIGHTS_OFF},
	{"rom:/right_vent_empty.ci8.sprite",                  CS_LIGHTS_ON},
	{"rom:/right_vent_dark.ci8.sprite",  CS_LIGHTS_OFF | CS_TOY_BONNIE},
	{"rom:/right_vent_bonnie.ci8.sprite", CS_LIGHTS_ON | CS_TOY_BONNIE},
};

CameraState mainHallStates[] = {
	{"rom:/main_hall_empty_dark.ci8.sprite", CS_LIGHTS_OFF},
	{"rom:/main_hall_empty_light.ci8.sprite", CS_LIGHTS_ON},
};

CameraState partsStates[] = {
	{"rom:/parts_dark.ci8.sprite", CS_LIGHTS_OFF},
	{"rom:/parts_empty.ci8.sprite", CS_LIGHTS_ON},
};

CameraState stageStates[] = {
	{"rom:/stage_empty.ci8.sprite",                    CS_LIGHTS_OFF},
	{"rom:/stage_empty.ci8.sprite",                     CS_LIGHTS_ON},
	{"rom:/stage_all_dark.ci8.sprite", CS_LIGHTS_OFF | CS_TOY_BONNIE},
	{"rom:/stage_all_light.ci8.sprite", CS_LIGHTS_ON | CS_TOY_BONNIE},
};

CameraState gameAreaStates[] = {
	{"rom:/game_area_empty_dark.ci8.sprite", CS_LIGHTS_OFF},
	{"rom:/game_area_empty_light.ci8.sprite",  CS_LIGHTS_ON},
};

CameraState prizeCornerStates[] = {
	{"rom:/prize_corner_dark.ci8.sprite", CS_LIGHTS_OFF},
	{"rom:/prize_corner_empty.ci8.sprite",  CS_LIGHTS_ON},
};

CameraState kidsCoveStates[] = {
	{"rom:/kids_cove_dark.ci8.sprite", CS_LIGHTS_OFF},
	{"rom:/kids_cove_empty.ci8.sprite",  CS_LIGHTS_ON},
};

CameraState *allCameraStates[] = {
	party1States, party2States, party3States, party4States,
	leftVentStates, rightVentStates, mainHallStates, partsStates,
	stageStates, gameAreaStates, prizeCornerStates, kidsCoveStates,
};

const char *CameraStateGetPath(int *states, int camSelected)
{
	int state = states[camSelected];
	if(allCameraStates[camSelected][state].state == state)
		return allCameraStates[camSelected][state].path;
	return NULL;
}
