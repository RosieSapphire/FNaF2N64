#include "perspective.h"
#include <stdbool.h>
#include <libdragon.h>
#include "util.h"

surface_t perspBuffer;
rspq_block_t *perspBlock;

void PerspectiveInit(void)
{
	perspBuffer = surface_alloc(FMT_RGBA16, 320, 240);
	rspq_block_begin();
	rdpq_set_mode_copy(false);
	int numDivs = 40;
	int divWidth = 320 / numDivs;
	for(int i = 0; i < numDivs; i++) {
		float iDist = fabs((float)(i - (numDivs >> 1)));
		float scaleY = (iDist * 0.026f);
		scaleY *= scaleY;
		scaleY += 1;
		const rdpq_blitparms_t parms = {
			.width = divWidth,
			.s0 = divWidth * i,
			.scale_y = scaleY,
			.cx = 0, .cy = 120,
		};
		rdpq_tex_blit(&perspBuffer, divWidth * i, 120, &parms);
	}
	perspBlock = rspq_block_end();
}

void PerspectiveBegin(void)
{
	rdpq_attach(&perspBuffer, NULL);
}

void PerspectiveEnd(void)
{
	rdpq_detach();
	rspq_block_run(perspBlock);
}
