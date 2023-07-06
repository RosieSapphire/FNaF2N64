#include "main_game.h"
#include "office.h"

void MainGameDraw(void)
{
	OfficeDraw();
}

void MainGameUpdate(float dt, struct controller_data held,
		struct controller_data down)
{
	OfficeUpdate(dt, held, down);
}
