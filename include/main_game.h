#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include <libdragon.h>

void MainGameDraw(void);
void MainGameUpdate(float dt, struct controller_data held,
		struct controller_data down);

#endif /* MAIN_GAME_H */
