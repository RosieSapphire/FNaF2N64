#ifndef OFFICE_H
#define OFFICE_H

#include <libdragon.h>

extern float officeTurn;

void OfficeLoad(void);
void OfficeUnload(void);
void OfficeDraw(void);
void OfficeUpdate(double dt, struct controller_data held,
		struct controller_data down);

#endif /* OFFICE_H */
