#ifndef BLIP_H
#define BLIP_H

#include <stdbool.h>

void BlipLoad(void);
void BlipDraw(void);
void BlipUpdate(float dt);
void BlipTrigger(bool visual, int which);

#endif /* BLIP_H */
