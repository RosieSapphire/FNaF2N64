#include "lights.h"
#include "office.h"
#include "object.h"
#include "sfx.h"
#include "mask.h"
#include "camera.h"

#define LEFT_LIGHT_ACTIVE_TURN -84
#define LEFT_LIGHT_VISIBLE_TURN -181
#define RIGHT_LIGHT_ACTIVE_TURN -472
#define RIGHT_LIGHT_VISIBLE_TURN -404

Object left[2];
const char *leftPaths[2] = {
	"rom:/light_left_off.ci8.sprite",
	"rom:/light_left_on.ci8.sprite",
};

Object right[2];
const char *rightPaths[2] = {
	"rom:/light_right_off.ci8.sprite",
	"rom:/light_right_on.ci8.sprite",
};

Object batteryIcons[5];
const char *batteryIconPaths[5] = {
	"rom:/battery_life0.ia4.sprite",
	"rom:/battery_life1.ia4.sprite",
	"rom:/battery_life2.ia4.sprite",
	"rom:/battery_life3.ia4.sprite",
	"rom:/battery_life4.ia4.sprite",
};

enum LightState lightState = LIGHT_OFF;

void LightsLoad(void)
{
	ObjectsLoad(left, 2, leftPaths);
	ObjectsLoad(right, 2, rightPaths);
	ObjectsLoad(batteryIcons, 5, batteryIconPaths);
}

void LightsUnload(void)
{
	ObjectsUnload(left, 2);
	ObjectsUnload(right, 2);
	ObjectsUnload(batteryIcons, 5);
}

void LightsDraw(void)
{
	if(MaskAtEnd() || isCameraVisible)
		return;

	if(officeTurn >= LEFT_LIGHT_VISIBLE_TURN)
		ObjectDraw(left[lightState == LIGHT_LEFT],
				147 + officeTurn, 429, 28, 42);
	if(officeTurn <= RIGHT_LIGHT_VISIBLE_TURN)
		ObjectDraw(right[lightState == LIGHT_RIGHT],
				1444 + officeTurn, 427, 29, 42);
}

void LightsUpdate(struct controller_data held)
{
	bool isTurnedLeft = officeTurn >= LEFT_LIGHT_ACTIVE_TURN;
	bool isTurnedRight = officeTurn <= RIGHT_LIGHT_ACTIVE_TURN;
	lightState = LIGHT_OFF;

	if(!isMaskOn && !isCameraVisible) {
		if(held.c->A && !isTurnedLeft && !isTurnedRight)
			lightState = LIGHT_CENTER;
	
		if(held.c->B) {
			if(isTurnedLeft)
				lightState = LIGHT_LEFT;
	
			if(isTurnedRight)
				lightState = LIGHT_RIGHT;
		}
	}

	float humVolume = 0.4f * (lightState > 0);
	mixer_ch_set_vol(SFXC_LIGHT_HUM, humVolume, humVolume);

}
