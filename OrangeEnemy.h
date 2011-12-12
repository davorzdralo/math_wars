#ifndef _ORANGE_ENEMY_H
#define _ORANGE_ENEMY_H

#include "ActiveEntity.h"
#include "Point.h"
#include "Enemy.h"
#include "Vector.h"

class GameWindow;

class OrangeEnemy : public Enemy
{
public:
	OrangeEnemy(GameWindow* parent, const Point& location);
	OrangeEnemy(GameWindow* parent, const Point& location, Vector direction);
	~OrangeEnemy();

	void update();

private:
	void initialize();

};

#endif /* _ORANGE_ENEMY_H */
