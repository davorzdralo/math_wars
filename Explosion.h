#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "GameWindow.h"

class Explosion
{
public:
    Explosion(GameWindow* parent, Point start, const char* textureName, int maxNumberOfParticles = 20, int minNumberOfParticles = 10);
};

#endif /* _EXPLOSION_H_ */
