#include "BlueEnemy.h"
#include "GameWindow.h"
#include "Point.h"
#include "Explosion.h"
#include <cmath>
#define PI 3.141



BlueEnemy::BlueEnemy(GameWindow* parent, const Point& location)
: 	Enemy(parent, location, "resources/blue.png", 1.0f, 0.0f, 0.2, 
		(double) rand() / RAND_MAX * 90, 0.6f) // Enemy(GameWindow* parent, const Point& location, const char* textureFileName, GLdouble size, 
											   // GLdouble textureAngleOffset, double speed, double angle, double collisionRadius)
{
	direction = Vector((double) rand() / RAND_MAX * 360);
	initialize();
}

BlueEnemy::BlueEnemy(GameWindow* parent, const Point& location, Vector direction)
: 	Enemy(parent, location, "resources/blue.png", 1.0f, 0.0f, 0.2, 
		(double) rand() / RAND_MAX * 90, 0.6f)
{

	this->direction = direction;
	initialize();
}

BlueEnemy::~BlueEnemy()
{
	Explosion e = Explosion(parent, location, "resources/blueParticle.png");
	parent->addToHighScore(100);
}

void BlueEnemy::initialize()
{
	rotationPerUpdate = 15;
	this->parent = parent;
	angle = direction.getAngle();
	dodgeSpeed = 0.2;
}

void BlueEnemy::update()
{   
	angle += rotationPerUpdate;
	double minimumDodgeDistance = 8;
	bool dodged = false;
	
	//izbegavanje

	for(unsigned i = 0; i < parent->getProjectiles().size(); i++)
	{
		double distance = parent->getProjectiles().at(i)->getLocation().distance(location);
		
		if(distance < minimumDodgeDistance)
		{
			double projectileAngle = parent->getProjectiles().at(i)->getAngle();
			double projectileToEnemyAngle = Vector(parent->getProjectiles().at(i)->getLocation(), location).getAngle();
			double margin = asin(size / distance) * 180/PI;
			double temp = fabs(projectileAngle - projectileToEnemyAngle);
			if(temp > 180)
				temp = 360 - temp;

			if(temp < margin)
			{
				double t = projectileAngle - projectileToEnemyAngle;
				if(t > 180)	t = 360 - t;
				if(t < -180) t = (360 - t) * -1;
				if(t > 0)
					direction = Vector(projectileToEnemyAngle + 180 + 90);
				else
					direction = Vector(projectileToEnemyAngle + 180 - 90);
				dodged = true;
				break;
			}
		}
	}
      
	// krecemo se direktno prema igracu
	if(!dodged)
		direction = Vector(location, parent->getPlayerLocation());

	if(direction.getX() || direction.getY())
		direction = direction.normalized();
	if(dodged)
	{
		location.x += direction.getX() * dodgeSpeed;
		location.y += direction.getY() * dodgeSpeed;
	}
	else
	{
		location.x += direction.getX() * speed;
		location.y += direction.getY() * speed;
	}

	if(location.x < -Globals::worldWidth/2 + boundingCircle.getRadius())
		location.x = -Globals::worldWidth/2 + boundingCircle.getRadius();
	
	if(location.x > Globals::worldWidth/2 - boundingCircle.getRadius())
		location.x = Globals::worldWidth/2 - boundingCircle.getRadius();
	
	if(location.y < -Globals::worldHeight/2 + boundingCircle.getRadius())
		location.y = -Globals::worldHeight/2 + boundingCircle.getRadius();
	
	if(location.y > Globals::worldHeight/2 - boundingCircle.getRadius())
		location.y = Globals::worldHeight/2 - boundingCircle.getRadius();
	

	boundingCircle.setCenter(location);
	
}


