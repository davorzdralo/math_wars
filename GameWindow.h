#ifndef _GAME_WINDOW_H_
#define	_GAME_WINDOW_H_

#include "Player.h"
#include "Grid.h"
#include "Circle.h"
#include "Projectile.h"
#include "Point.h"
#include "Particle.h"
#include "GUI.h"
#include "Enemy.h"
#include <vector>

class GameWindow
{
public:
	GameWindow();
	~GameWindow();
	void update();
	void draw() const;
	void addProjectile(Projectile* projectile);
	std::vector<Projectile*>& getProjectiles();
	void addParticle(Particle* particle);
	const Point& getViewLocation() const;
	const Point& getPlayerLocation() const;
	unsigned getLivesRemaining() const;
	void killAllEntities();
	void addToHighScore(unsigned additonalPoints);
private:
	void removeDead();
	void checkCollisions();
	void spawnEnemies();
	void spawnOrangeEnemies();

	bool isInFullScreen;
	Player* player;
	Grid* grid;
	GUI* gui;
	Point viewLocation;
	
	std::vector<Projectile*> projectiles;
	std::vector<Enemy*> enemies;
	std::vector<Particle*> particles;
	
	static const int greenEnemySpawnTime = 400; // milis
	static const int orangeEnemySpawnTime = 5000; // milis
	static const int blueEnemySpawnTime = 1500; // milis
	int lastGreenSpawned;
	int lastOrangeSpawned;
	int lastBlueSpawned;
};

#endif	/* _GAME_WINDOW_H_ */
