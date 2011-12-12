#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "Point.h"
#include "Vector.h"
#include "ActiveEntity.h"

class GameWindow;

class Projectile : public ActiveEntity
{
public:
    Projectile(GameWindow* parent, const Point& start, Vector direction);
	~Projectile();
	void draw() const;
	void update();
	double getAngle();
protected:
	GameWindow* parent;
	Vector direction;
};

#endif /* _PROJECTILE_H_ */
