#ifndef MASK_H
#define MASK_H

#include <libdragon.h>

extern bool isMaskOn;

void MaskLoad(void);
void MaskUnload(void);
void MaskDraw(void);
void MaskUpdate(double dt, struct controller_data down);
bool MaskAtStart(void);
bool MaskAtEnd(void);
bool MaskAtStartOrEnd(void);

#endif /* MASK_H */
