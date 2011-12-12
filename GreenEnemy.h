#ifndef _GREEN_ENEMY_H_
#define _GREEN_ENEMY_H_

#include "ActiveEntity.h"
#include "Point.h"
#include "Enemy.h"
#include "Vector.h"

class GameWindow;

class GreenEnemy : public Enemy
{
public:
	GreenEnemy(GameWindow* parent, const Point& location);
	~GreenEnemy();

	void update();

private:

};

#endif /* _GREEN_ENEMY_H_ */
