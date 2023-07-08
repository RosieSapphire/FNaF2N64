#ifndef MUSIC_BOX_H
#define MUSIC_BOX_H

#include <libdragon.h>

void MusicBoxLoad(void);
void MusicBoxUnload(void);
void MusicBoxUpdate(double dt, struct controller_data held);
void MusicBoxDraw(void);

#endif /* MUSIC_BOX_H */
