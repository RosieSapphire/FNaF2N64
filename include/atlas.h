#ifndef Atlas_H_
#define Atlas_H_

#include <libdragon.h>
#include "object.h"

typedef struct {
	Object obj;
	int numX, segW, segH;
} Atlas;

void AtlasLoad(Atlas *a, const char *path, int segW, int segH);
void AtlasDraw(Atlas a, int px, int py, int ind);
void AtlasUnload(Atlas *a);

#endif /* Atlas_H_ */
