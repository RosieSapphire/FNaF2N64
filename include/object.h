#ifndef OBJECT_H_
#define OBJECT_H_

#include <libdragon.h>

typedef struct {
	sprite_t *spr;
	bool isLoaded;
} Object;

void ObjectLoad(Object *o, const char *path);
void ObjectsLoad(Object *o, int num, const char **paths);
void ObjectUnload(Object *o);
void ObjectsUnload(Object *o, int num);
void ObjectDraw(Object o, int posX, int posY, int originX, int originY);
void ObjectDebug(double dt);

#endif /* OBJECT_H_ */
