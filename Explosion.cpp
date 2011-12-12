#include "Explosion.h"
#include <cmath>

#define PI 3.14159265

Explosion::Explosion(GameWindow* parent, Point start, const char* textureName, 	int maxNumberOfParticles, int minNumberOfParticles)
{
	int numberOfParticles = (int) ((double)rand() / RAND_MAX) * (maxNumberOfParticles - minNumberOfParticles) + minNumberOfParticles;
	for(int i = 0; i < numberOfParticles; i++)
	{	
		double angle = ((double)rand() / RAND_MAX) * 360;
		Vector direction = Vector(angle, 1);
		parent->addParticle(new Particle(start, direction, textureName));
	}
}
