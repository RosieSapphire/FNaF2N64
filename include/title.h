#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "scene.h"
#include <libdragon.h>

void TitleLoad(void);
void TitleUnload(void);
void TitleDraw(void);
enum Scene TitleUpdate(float dt, struct controller_data down);

#endif /* TITLE_SCREEN_H */
