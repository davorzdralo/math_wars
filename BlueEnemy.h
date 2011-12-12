#ifndef _BLUE_ENEMY_H
#define _BLUE_ENEMY_H

#include "ActiveEntity.h"
#include "Point.h"
#include "Enemy.h"
#include "Vector.h"

class GameWindow;

class BlueEnemy : public Enemy
{
public:
	BlueEnemy(GameWindow* parent, const Point& location);
	BlueEnemy(GameWindow* parent, const Point& location, Vector direction);
	~BlueEnemy();

	void update();

private:
	void initialize();
	double dodgeSpeed;

};

#endif /* _BLUE_ENEMY_H */
