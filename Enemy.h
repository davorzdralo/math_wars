#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "ActiveEntity.h"
#include "Point.h"
#include "Vector.h"

class GameWindow;

class Enemy : public ActiveEntity
{
public:
	Enemy(GameWindow* parent, const Point& location, const char* textureFileName, GLdouble size, 
		GLdouble textureAngleOffset, double speed, double angle, double collisionRadius);

	void draw() const;
	virtual void update() = 0;
	const Point& getLocation() const;

protected:
	void initialize(GameWindow* parent);
	GameWindow* parent;
	double rotationPerUpdate; // how much entity rotates per update in degrees
	Vector direction;
};

#endif /* _ENEMY_H_ */
