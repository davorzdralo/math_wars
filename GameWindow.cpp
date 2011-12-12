#include <GL/glut.h>
#include "GameWindow.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Globals.h"
#include "GreenEnemy.h"
#include "OrangeEnemy.h"
#include "BlueEnemy.h"
#include <iostream>
#include <cmath>
#include <ctime>

#define PI 3.141

GameWindow::GameWindow()
{
	player = new Player(this);
	grid = new Grid(this);
	gui = new GUI(this);
	
	lastGreenSpawned = 0;
	lastOrangeSpawned = 0;
	lastBlueSpawned = 0;
	isInFullScreen = true;

	time_t rawTime;
	time (&rawTime);
	srand(rawTime);
}

GameWindow::~GameWindow()
{
	delete grid;
}

void GameWindow::update()
{
	if(Keyboard::instance()->isPressed(27))
		exit(0);
	if(Keyboard::instance()->isPressed('f'))
	{
		if(isInFullScreen)
			glutReshapeWindow(1024, 768);
		else
			glutFullScreen();
		isInFullScreen = !isInFullScreen;
	}
	
		
	if(player->isDead() && player->getLivesRemaining() > 0)
	{
		if(glutGet(GLUT_ELAPSED_TIME) - player->getDeathTimeStamp() > 3000)
			player->resurrect();
	}
	else if(!player->isDead() && player->getLivesRemaining() > 0)
	{
		spawnEnemies();
		player->update();
		checkCollisions();


		// izracunava lokaciju "kamere" na osnovu lokacije igraca.
		viewLocation.x = player->getLocation().x - (player->getLocation().x + Globals::worldWidth/2) 
		* Globals::viewWidth / Globals::worldWidth + Globals::viewWidth/2;
		viewLocation.y = player->getLocation().y - (player->getLocation().y + Globals::worldHeight/2) 
			* Globals::viewHeight / Globals::worldHeight + Globals::viewHeight/2;

		// dodamo margine
		double margina = 0.50; // u %
		viewLocation.x += viewLocation.x * margina;
		viewLocation.y += viewLocation.y * margina;

		// ovo mi se ni malo ne svidja ovako.....
		Mouse::instance()->setViewLocation(viewLocation);
	}
	
	removeDead();
	grid->update();

	for(unsigned i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->update();

	for(unsigned i = 0; i < enemies.size(); i++)
		enemies.at(i)->update();

	for(unsigned i = 0; i < particles.size(); i++)
		particles.at(i)->update();
	
	
}

void GameWindow::removeDead()
{
	for(unsigned i = 0; i < projectiles.size(); i++)
	{
		if(projectiles.at(i)->isDead())
		{
			delete projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);
		}
	}
	
	for(unsigned i = 0; i < enemies.size(); i++)
	{
		if(enemies.at(i)->isDead())
		{
			delete enemies.at(i); // brisemo memoriju koju zauzima objekat
			enemies.erase(enemies.begin() + i); // brisemo pokazivac na objekat sa liste
		}
	}

	for(unsigned i = 0; i < particles.size(); i++)
	{
		if(particles.at(i)->isDead())
		{
			delete particles.at(i); // brisemo memoriju koju zauzima objekat
			particles.erase(particles.begin() + i); // brisemo pokazivac na objekat sa liste
		}
	}
}

void GameWindow::checkCollisions()
{
	for(unsigned i = 0; i < enemies.size(); i++)
	{
		if(!(player->isDead()) && !(enemies.at(i)->isDead())
				&& player->collides(enemies.at(i)))
		{
			player->die();
			break;
		}
	}

	// proveravamo koliziju izmedju projektila i neprijatelja
	for(unsigned i = 0; i < projectiles.size(); i++)
	{
		for(unsigned j = 0; j < enemies.size(); j++)
		{
			if(!(projectiles.at(i)->isDead()) && !(enemies.at(j)->isDead())
				&& projectiles.at(i)->collides(enemies.at(j)))
			{
				projectiles.at(i)->setDead(true);
				enemies.at(j)->setDead(true);
				// ako su se sudarili, unisteni su, preskacemo dalje provere za
				// dati par projektil/neprijatelj
				break;
			}
		}
	}
}

void GameWindow::draw() const
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(-viewLocation.x, -viewLocation.y, 0);
	grid->draw();
	if(!player->isDead())
		player->draw();
	
	
	Mouse::instance()->draw();
	
	for(unsigned i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->draw();

	for(unsigned i = 0; i < particles.size(); i++)
		particles.at(i)->draw();
	
	for(unsigned i = 0; i < enemies.size(); i++)
		enemies.at(i)->draw();
		
	gui->draw();
		
	glPopMatrix();

	glutSwapBuffers();
}

void GameWindow::spawnEnemies()
{
		
	if((glutGet(GLUT_ELAPSED_TIME) - lastGreenSpawned) > greenEnemySpawnTime)
	{
		lastGreenSpawned = glutGet(GLUT_ELAPSED_TIME);
		Point temp;

		do{		
			temp.x =  rand() % (int) Globals::worldWidth - Globals::worldWidth / 2;
			temp.y = rand() % (int) Globals::worldHeight - Globals::worldHeight / 2;
		}
		while(temp.distance(getPlayerLocation()) < 10);
		

		enemies.push_back(new GreenEnemy(this, temp));
	}
	if((glutGet(GLUT_ELAPSED_TIME) - lastOrangeSpawned) > orangeEnemySpawnTime)
	{
		lastOrangeSpawned = glutGet(GLUT_ELAPSED_TIME);
		spawnOrangeEnemies();
		
	}
	if((glutGet(GLUT_ELAPSED_TIME) - lastBlueSpawned) > blueEnemySpawnTime)
	{
		lastBlueSpawned = glutGet(GLUT_ELAPSED_TIME);
		Point temp;

		do{		
			temp.x =  rand() % (int) Globals::worldWidth - Globals::worldWidth / 2;
			temp.y = rand() % (int) Globals::worldHeight - Globals::worldHeight / 2;
		}
		while(temp.distance(getPlayerLocation()) < 10);
		

		enemies.push_back(new BlueEnemy(this, temp));
	}
	
}

void GameWindow::spawnOrangeEnemies()
{
	double distanceFromEdge = 5;
	Point spawnLocation;
	int numberOfEnemies = 20;
	double radiusOfSpawning = 1;
	
	Point northWest = Point(-Globals::worldWidth / 2 + distanceFromEdge, Globals::worldHeight / 2 - distanceFromEdge);
	Point northEast = Point(Globals::worldWidth / 2 - distanceFromEdge, Globals::worldHeight / 2 - distanceFromEdge);
	Point southWest = Point(-Globals::worldWidth / 2 + distanceFromEdge, -Globals::worldHeight / 2 + distanceFromEdge);
	Point southEast = Point(Globals::worldWidth / 2 - distanceFromEdge, -Globals::worldHeight / 2 + distanceFromEdge);

	do
	{
		int quadrant = rand() % 5;
		if(quadrant == 0)
			spawnLocation = Point(0, 0);
		else if(quadrant == 1)
			spawnLocation = northWest;
		else if(quadrant == 2)
			spawnLocation = northEast;
		else if(quadrant == 3)
			spawnLocation = southWest;
		else if(quadrant == 4)
			spawnLocation = southEast;
	} 
	while (spawnLocation.distance(player->getLocation()) < 5);

	for(int i = 0; i < numberOfEnemies; i++)
	{	
		Point tempLocation = Point(cos((double)i / numberOfEnemies * PI * 2) * radiusOfSpawning + spawnLocation.x,
								   sin((double)i / numberOfEnemies * PI * 2) * radiusOfSpawning + spawnLocation.y);
		Vector direction = Vector(spawnLocation, tempLocation);
		enemies.push_back(new OrangeEnemy(this, tempLocation, direction));

	}
	
}

void GameWindow::killAllEntities()
{
	for(unsigned i = 0; i < projectiles.size(); i++)
		projectiles.at(i)->setDead(true);
	
	for(unsigned i = 0; i < enemies.size(); i++)
		enemies.at(i)->setDead(true);
}

void GameWindow::addProjectile(Projectile* projectile)
{
	projectiles.push_back(projectile);
}

void GameWindow::addParticle(Particle* particle)
{
	particles.push_back(particle);
}

const Point& GameWindow::getViewLocation() const
{
	return viewLocation;
}

const Point& GameWindow::getPlayerLocation() const
{
	return player->getLocation();
}

std::vector<Projectile*>& GameWindow::getProjectiles()
{
	return projectiles;
}

unsigned GameWindow::getLivesRemaining() const
{
	return player->getLivesRemaining();
}

void GameWindow::addToHighScore(unsigned additonalPoints)
{
	gui->addToHighScore(additonalPoints);
}








