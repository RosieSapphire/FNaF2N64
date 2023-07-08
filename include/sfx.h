#ifndef SFX_CHANNELS_H_
#define SFX_CHANNELS_H_

#include <libdragon.h>

enum SFXChannels {
	SFXC_AMBIENCE,
	SFXC_LIGHT_HUM,
	SFXC_CAMERA_FLIP,
	SFXC_CAMERA_DRONE,
	SFXC_MASK_FLIP,
	SFXC_MASK_BREATH,
	SFXC_FAN,
	SFXC_BLIP,
	SFXC_STATIC,
	SFXC_COUNT,
};

extern wav64_t lightHumSFX, fanSFX, noseHonkSFX, maskOnSFX, maskOffSFX,
       maskBreathSFX, blipSFX1, blipSFX2, titleMusic, staticSFX, camUpSFX,
       camDownSFX, camDroneSFX;

void SFXLoad(void);
void MixerStopEverything(void);

#endif /* SFX_CHANNELS_H_ */
