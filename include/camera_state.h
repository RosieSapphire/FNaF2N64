#ifndef CAMERA_STATE_H
#define CAMERA_STATE_H

#define CS_LIGHTS_OFF 0x0
#define CS_LIGHTS_ON  0x1
#define CS_TOY_BONNIE 0x2

const char *CameraStateGetPath(int *states, int camSelected);

#endif /* CAMERA_STATE_H */
