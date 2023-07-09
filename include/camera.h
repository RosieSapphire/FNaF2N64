#ifndef CAMERA_H
#define CAMERA_H

#include <libdragon.h>

extern bool isCameraUsingLast;
extern bool isCameraVisibleLast;
extern bool isCameraUsing;
extern bool isCameraVisible;

enum CameraStates {
	CAM_01, CAM_02, CAM_03,
	CAM_04, CAM_05, CAM_06,
	CAM_07, CAM_08,CAM_09,
	CAM_10,CAM_11,CAM_12,
	CAM_COUNT,
};

extern enum CameraStates camSelected;

void CameraFlipLoad(void);
void CameraFlipUnload(void);
void CameraUILoad(void);
void CameraUIUnload(void);
void CameraViewsUnload(bool excludeUsing);
bool CameraFlipAtStart(void);
bool CameraFlipAtEnd(void);
bool CameraFlipAtStartOrEnd(void);
void CameraFlipDraw(void);
void CameraUIDraw(void);
void CameraFlipUpdate(double dt, struct controller_data down);
void CameraViewDraw(void);
void CameraViewUpdate(double dt, struct controller_data down);

#endif /* MASK_H */
