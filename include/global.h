#ifndef GLOBAL_H
#define GLOBAL_H

#include <libdragon.h>

extern rdpq_font_t *pixelFont, *ocrFont1, *ocrFont2, *largeFont;

void GlobalLoad(void);
void GlobalUpdate(float dt);

#endif /* GLOBAL_H */
