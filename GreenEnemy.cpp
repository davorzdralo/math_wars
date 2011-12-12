#include "GreenEnemy.h"
#include "GameWindow.h"
#include "Explosion.h"
#include "Point.h"


GreenEnemy::GreenEnemy(GameWindow* parent, const Point& location)
: 	Enemy(parent, location, "resources/green.png", 1.0f, 0.0f, 0.13, 
		(double) rand() / RAND_MAX * 90, 0.6f)
{
	rotationPerUpdate = 5;
	this->parent = parent;
}

GreenEnemy::~GreenEnemy()
{
	Explosion e = Explosion(parent, location, "resources/greenParticle.png");
	parent->addToHighScore(50);
}

void GreenEnemy::update()
{   
	angle += rotationPerUpdate;
      
	// krecemo se direktno prema igracu
	direction = Vector(location, parent->getPlayerLocation());
	if(direction.getX() || direction.getY())
		direction = direction.normalized();
	
	location.x += direction.getX() * speed;
	location.y += direction.getY() * speed;

	// sprecavamo izlazak van "terena"
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


