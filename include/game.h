#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include <libdragon.h>

void GameLoad(void);
void GameUnload(void);
void GameDraw(void);
enum Scene GameUpdate(double dt, struct controller_data down,
		struct controller_data held);

#endif /* MAIN_GAME_H */
