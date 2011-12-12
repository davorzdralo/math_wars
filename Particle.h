#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Point.h"
#include "Vector.h"
#include "ActiveEntity.h"

class GameWindow;

class Particle : public ActiveEntity
{
public:
    Particle(const Point& start, Vector direction, const char* textureName);
	void draw() const;
	void update();
protected:
	Vector direction;
	double lenght;
	double shorteningRate;
	double maxSpeed;
	double minSpeed;
};

#endif /* _PARTICLE_H_ */
