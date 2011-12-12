#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ActiveEntity.h"
#include "Vector.h"
#include <ctime>

class GameWindow;

class Player : public ActiveEntity
{
public:
	Player(GameWindow* parent);

	void draw() const;
	void update();
	const Point& getLocation() const;
	void die();
	double getDeathTimeStamp();
	void resurrect();
	unsigned getLivesRemaining() const;

private:
	unsigned livesRemaining;
	long lastFired;
	GameWindow* parent;

	Vector direction;
	double deathTimeStamp;

	static const int cooldown = 100;
	static const int maxRotation = 15;
};

#endif /* _PLAYER_H_ */
