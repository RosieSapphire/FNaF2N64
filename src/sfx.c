#include "sfx.h"

wav64_t lightHumSFX, fanSFX, noseHonkSFX, maskOnSFX, maskOffSFX,
       maskBreathSFX, blipSFX1, blipSFX2, titleMusic, staticSFX, camUpSFX,
       camDownSFX, camDroneSFX, boxMusic, windSFX;

void SFXLoad(void)
{
	mixer_ch_set_vol(SFXC_LIGHT_HUM, 0.6f, 0.6f);
	wav64_open(&lightHumSFX, "rom:/light_buzz.wav64");
	wav64_set_loop(&lightHumSFX, true);

	mixer_ch_set_vol(SFXC_FAN, 0.4f, 0.4f); // 40% if out of cams, 25% if in
	wav64_open(&fanSFX, "rom:/fan.wav64");
	wav64_set_loop(&fanSFX, true);

	mixer_ch_set_vol(SFXC_BLIP, 0.5f, 0.5f);
	wav64_open(&noseHonkSFX, "rom:/nose_honk.wav64");

	mixer_ch_set_vol(SFXC_MASK_FLIP, 0.5f, 0.5f);
	wav64_open(&maskOnSFX, "rom:/mask_on.wav64");
	wav64_open(&maskOffSFX, "rom:/mask_off.wav64");

	mixer_ch_set_vol(SFXC_MASK_BREATH, 0.6f, 0.6f);
	wav64_open(&maskBreathSFX, "rom:/mask_breath.wav64");
	wav64_set_loop(&maskBreathSFX, true);

	mixer_ch_set_vol(SFXC_BLIP, 0.5f, 0.5f);
	wav64_open(&blipSFX1, "rom:/blip.wav64");
	wav64_open(&blipSFX2, "rom:/blip2.wav64");

	mixer_ch_set_vol(SFXC_BLIP, 0.5f, 0.5f);
	wav64_open(&blipSFX1, "rom:/blip.wav64");
	wav64_open(&blipSFX2, "rom:/blip2.wav64");

	mixer_ch_set_vol(SFXC_AMBIENCE, 1.0f, 1.0f);
	wav64_open(&titleMusic, "rom:/title_music.wav64");
	wav64_set_loop(&titleMusic, true);

	mixer_ch_set_vol(SFXC_STATIC, 0.5f, 0.5f);
	wav64_open(&staticSFX, "rom:/static.wav64");

	mixer_ch_set_vol(SFXC_CAMERA_FLIP, 0.5f, 0.5f);
	wav64_open(&camUpSFX, "rom:/cam_open.wav64");
	wav64_open(&camDownSFX, "rom:/cam_close.wav64");

	mixer_ch_set_vol(SFXC_CAMERA_DRONE, 0.0f, 0.0f);
	wav64_open(&camDroneSFX, "rom:/cam_drone.wav64");
	wav64_set_loop(&camDroneSFX, true);

	mixer_ch_set_vol(SFXC_MUSIC_BOX, 0.0f, 0.0f);
	wav64_open(&boxMusic, "rom:/music_box.wav64");
	wav64_set_loop(&boxMusic, true);

	wav64_open(&windSFX, "rom:/wind.wav64");
}

void MixerStopEverything(void)
{
	for(int i = 0; i < SFXC_COUNT; i++)
		mixer_ch_stop(i);
}
