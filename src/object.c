#include "object.h"
#include "util.h"

double debugTimer = 0.0;
double lastLoad = 0.0;
int loads = 0;
int unloads = 0;

void ObjectLoad(Object *o, const char *path)
{
	if(o->isLoaded)
		return;
	o->spr = sprite_load(path);
	o->isLoaded = true;
	lastLoad = debugTimer;
	loads++;
}

void ObjectsLoad(Object *o, int num, const char **paths)
{
	for(int i = 0; i < num; i++)
		ObjectLoad(o + i, paths[i]);
}

void ObjectUnload(Object *o)
{
	if(!o->isLoaded)
		return;

	sprite_free(o->spr);
	o->isLoaded = false;
	unloads++;
}

void ObjectsUnload(Object *o, int num)
{
	for(int i = 0; i < num; i++)
		ObjectUnload(o + i);
}

void ObjectDraw(Object o, int posX, int posY, int originX, int originY)
{
	const rdpq_blitparms_t parms = {
		.cx = VCon(originX),
		.cy = VCon(originY),
	};

	rdpq_sprite_blit(o.spr, VCon(posX), VCon(posY), &parms);
}

void ObjectDebug(double dt)
{
	debugTimer += dt;
	debugf("%d Local Objs, %d Global Objs (%d loads, %d unloads)\n"
			"Last Load %f secs ago\n\n",
			loads - unloads - 6, 6, loads,
			unloads, debugTimer - lastLoad);
}
