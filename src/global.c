#include "global.h"
#include "blip.h"
#include "static.h"

rdpq_font_t *pixelFont, *ocrFont1, *ocrFont2, *largeFont;

void GlobalLoad(void)
{
	BlipLoad();
	StaticLoad();
	pixelFont = rdpq_font_load("rom:/pixel.font64");
	ocrFont1 = rdpq_font_load("rom:/ocr.font64");
	ocrFont2 = rdpq_font_load("rom:/ocr2.font64");
	largeFont = rdpq_font_load("rom:/medium.font64");
}

void GlobalUpdate(float dt)
{
	BlipUpdate(dt);
	StaticUpdate(dt);
}
