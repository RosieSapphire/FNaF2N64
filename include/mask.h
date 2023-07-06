#ifndef MASK_H
#define MASK_H

#include <libdragon.h>

extern bool isMaskOn;

void MaskLoad(void);
void MaskUnload(void);
void MaskDraw(void);
void MaskUpdate(float dt, struct controller_data down);

#endif /* MASK_H */
