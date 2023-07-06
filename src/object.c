#include "object.h"
#include "util.h"
#include <malloc.h>
#include <string.h>

int objectsLoaded = 0;
float lastTimeLoaded = 0.0;
float debugTimer = 0.0;

void ObjectLoad(Object *o, const char *path)
{
	if(o->isLoaded)
		return;

	char *fullPath = malloc(strlen(path) + 5);
	strncpy(fullPath, "rom:/", 6);
	fullPath = strcat(fullPath, path);
	o->spr = sprite_load(fullPath);
	o->isLoaded = true;
	free(fullPath);
	objectsLoaded++;
	lastTimeLoaded = debugTimer;
}

void ObjectsLoad(Object *o, const char **paths, int num)
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
	objectsLoaded--;
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

void ObjectDrawFrame(Object *o, int posX, int posY, int originX,
		int originY, int ind, int max, const char **paths,
		bool unloadPrevious)
{
	if(unloadPrevious) {
		for(int i = 0; i < max; i++) {
			if(i == ind)
				continue;

			ObjectUnload(o + i);
		}
	}

	ObjectLoad(o + ind, paths[ind]);
	ObjectDraw(o[ind], posX, posY, originX, originY);
}

void ObjectsDebugLoaded(float timeNow)
{
	debugTimer = timeNow;
	debugf("Objects loaded %d\nTime since last load %.4lf\n\n",
			objectsLoaded, debugTimer - lastTimeLoaded);
}
