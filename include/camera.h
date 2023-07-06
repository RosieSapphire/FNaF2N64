#ifndef CAMERA_H
#define CAMERA_H

#include <libdragon.h>

extern bool camIsUsing, camIsVisible;

void CameraFlipLoad(void);
void CameraFlipUnload(void);
void CameraFlipDraw(void);
void CameraFlipUpdate(float dt, struct controller_data down);

#endif /* CAMERA_H */
