#ifndef OFFICE_H
#define OFFICE_H

#include <stdbool.h>
#include <libdragon.h>
#include "util.h"

extern float officeTurn;

void OfficeDraw(void);
void OfficeUpdate(float dt, struct controller_data held,
		struct controller_data down);

#endif /* OFFICE_H */
