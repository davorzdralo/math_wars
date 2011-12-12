#include "OrangeEnemy.h"
#include "GameWindow.h"
#include "Explosion.h"
#include "Point.h"


OrangeEnemy::OrangeEnemy(GameWindow* parent, const Point& location)
: 	Enemy(parent, location, "resources/orange.png", 1.0f, 0.0f, 0.13, 
		(double) rand() / RAND_MAX * 90, 0.6f)
{
	direction = Vector((double) rand() / RAND_MAX * 360);
	initialize();
}

OrangeEnemy::OrangeEnemy(GameWindow* parent, const Point& location, Vector direction)
: 	Enemy(parent, location, "resources/orange.png", 1.0f, 0.0f, 0.13, 
		(double) rand() / RAND_MAX * 90, 0.6f)
{

	this->direction = direction;
	initialize();
}

OrangeEnemy::~OrangeEnemy()
{
	Explosion e = Explosion(parent, location, "resources/orangeParticle.png");
	parent->addToHighScore(25);
}

void OrangeEnemy::initialize()
{
	rotationPerUpdate = 15;
	this->parent = parent;
	angle = direction.getAngle();
}

void OrangeEnemy::update()
{   
	angle += rotationPerUpdate;

	const double maximumChange = 45;
	double oldAngle = direction.getAngle();
    double offset = (double) rand() / RAND_MAX * maximumChange - maximumChange / 2;  
	double newAngle = oldAngle + offset;
	direction = Vector(newAngle);	


	direction = direction.normalized();
	
	location.x += direction.getX() * speed;
	location.y += direction.getY() * speed;


	if(location.x < -Globals::worldWidth/2 + boundingCircle.getRadius())
	{	
		location.x = -Globals::worldWidth/2 + boundingCircle.getRadius();
		direction.setX(-1 * direction.getX()); 
	}
	if(location.x > Globals::worldWidth/2 - boundingCircle.getRadius())
	{	
		location.x = Globals::worldWidth/2 - boundingCircle.getRadius();
		direction.setX(-1 * direction.getX());
	}
	if(location.y < -Globals::worldHeight/2 + boundingCircle.getRadius())
	{	
		location.y = -Globals::worldHeight/2 + boundingCircle.getRadius();
		direction.setY(-1 * direction.getY());
	}
	if(location.y > Globals::worldHeight/2 - boundingCircle.getRadius())
	{	
		location.y = Globals::worldHeight/2 - boundingCircle.getRadius();
		direction.setY(-1 * direction.getY());
	}
	boundingCircle.setCenter(location);
}


