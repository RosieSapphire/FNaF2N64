#ifndef TOY_BONNIE_H
#define TOY_BONNIE_H

#include <stdbool.h>

extern int toyBonnieAI;
extern int toyBonnieCamLast;
extern int toyBonnieCam;
extern float toyBonnieStunTimer;

void ToyBonnieScareLoad(void);
void ToyBonnieScareUnload(void);
void ToyBonnieUpdate(double dt);
void ToyBonnieScareDraw(void);

#endif /* TOY_BONNIE_H */
