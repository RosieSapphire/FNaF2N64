#ifndef LIGHTS_H
#define LIGHTS_H

#include <libdragon.h>

enum LightState {
	LIGHT_OFF,
	LIGHT_LEFT,
	LIGHT_CENTER,
	LIGHT_RIGHT,
	LIGHT_STATE_COUNT,
};

extern enum LightState lightState;

void LightsLoad(void);
void LightsUnload(void);
void LightsDraw(void);
void LightsUpdate(struct controller_data held);

#endif /* LIGHTS_H */
