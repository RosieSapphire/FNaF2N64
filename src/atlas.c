#include "atlas.h"
#include <malloc.h>
#include "util.h"

void AtlasLoad(Atlas *a, const char *path, int segW, int segH)
{
	if(a->obj.isLoaded)
		return;

	ObjectLoad(&a->obj, path);
	a->numX = a->obj.spr->width / segW;
	a->segW = segW;
	a->segH = segH;
}

void AtlasDraw(Atlas a, int px, int py, int ox, int oy, int ind)
{
	px = VCon(px);
	py = VCon(py);
	ox = VCon(ox);
	oy = VCon(oy);
	rdpq_mode_dithering(DITHER_NOISE_NONE);
	rdpq_mode_filter(FILTER_POINT);

	int x0 = px - ox;
	int x1 = x0 + a.segW;
	int y0 = py - oy;
	int y1 = y0 + a.segH + ind - ind;
	int ix = ind % a.numX;
	int iy = ind / a.numX;
	int s = ix * a.segW;
	int t = iy * a.segH;
	rdpq_sprite_upload(TILE0, a.obj.spr, NULL);
	rdpq_texture_rectangle(TILE0, x0, y0, x1, y1, s, t);
}

void AtlasUnload(Atlas *a)
{
	ObjectUnload(&a->obj);
}
