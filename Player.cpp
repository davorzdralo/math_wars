#include "Player.h"
#include "Keyboard.h"
#include <GL/glut.h>
#include "GameWindow.h"
#include "Explosion.h"
#include "Mouse.h"
#include "Vector.h"
#include "Projectile.h"
#include "ResourceCache.h"
#include <cmath>
#include <iostream>


float min(float a, float b)
{
	return a > b ? b : a;
}

float max(float a, float b)
{
	return a < b ? b : a;
}

Player::Player(GameWindow* parent)
: ActiveEntity(Point(0, 0), // starting location
               "resources/player.png", 
               0.9f, // size
               90,   // textureAngleOffset, 
               0.4f, // speed
               90,   // starting angle
               0.5f  // bounding circle radius
              )
{
	lastFired = 0; // time last fired, at start of program 0...
	livesRemaining = 3;
	this->parent = parent;
	direction = Vector(0, 1, 0);
}



void Player::draw() const
{
	//boundingCircle.draw();

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glPushMatrix();
	glTranslatef(location.x, location.y, 0);
	glRotatef(angle + textureAngleOffset, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    {
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(-size, size, 0.01);
        glTexCoord2f(0, 1); glVertex3f(-size, -size, 0.01);
        glTexCoord2f(1, 1); glVertex3f(size, -size, 0.01);
        glTexCoord2f(1, 0); glVertex3f(size, size, 0.01);
    }
    glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Player::update()
{
	direction.setX(0);
	direction.setY(0);

	if(Keyboard::instance()->isPressed('w'))
		direction.setY(1);
	if(Keyboard::instance()->isPressed('a'))
		direction.setX(-1);
	if(Keyboard::instance()->isPressed('s'))
		direction.setY(-1);
	if(Keyboard::instance()->isPressed('d'))
		direction.setX(1);

 	// ako je makar jedna koordinata razlicita od nule
 	// izvrsimo normalizaciju vektora pravca
 	// inace, moze brze: da se cuvaju vec normalizovani vektori 
 	// za svih 8 pravaca kretanja, ali to mozda nekad' kasnije
 	// necemo sad da izazivamo cika Knutha :D
	if(direction.getX() || direction.getY())
		direction = direction.normalized();

	location.x += direction.getX() * speed;
	location.y += direction.getY() * speed;
	location.z += direction.getZ() * speed;

	// Here be dragons!
	if(direction.getX() || direction.getY())
	{
		float targetAngle = atan2(direction.getY(), direction.getX()) * 180/3.14159265 + 360;
		if(targetAngle >= 360) 
			targetAngle -= 360;

		if(angle > 180 && targetAngle < 180)
			targetAngle += 360;

		float lowLimit = angle;
		float hiLimit = angle + 180;

		if(targetAngle >= lowLimit && targetAngle <= hiLimit)
			angle += min(maxRotation, abs(targetAngle - angle));
		else
			angle -= min(maxRotation, abs(targetAngle - angle));

		if(angle >= 360)
			angle -= 360;
		if(angle < 0)
			angle += 360;
	}
	// Dragons are no more!

	if((glutGet(GLUT_ELAPSED_TIME) - lastFired) > cooldown)
	{
		lastFired = glutGet(GLUT_ELAPSED_TIME);
		//TODO: ako su lokacije misa i nishana identicne, treba pucati ka 90 stepeni
		Vector directionFired(location, Mouse::instance()->getWorldLocation());
		double angleFired = directionFired.getAngle();
		double angleDiference = 1;
		
		parent->addProjectile(new Projectile(parent, location, Vector(angleFired-angleDiference, 1)));
		parent->addProjectile(new Projectile(parent, location, Vector(angleFired+angleDiference, 1)));
	}
	
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

const Point& Player::getLocation() const
{
	return location;
}

void Player::die()
{
	setDead(true);
	deathTimeStamp = glutGet(GLUT_ELAPSED_TIME);
	parent->killAllEntities();
	Explosion e = Explosion(parent, location, "resources/particle.png", 100, 70);
	livesRemaining--;
}

double Player::getDeathTimeStamp()
{
	return deathTimeStamp;
}

void Player::resurrect()
{
	setDead(false);
	location = Point(0, 0, 0);
	//TODO: spawn animacija
}

unsigned Player::getLivesRemaining() const
{
	return livesRemaining;
}


















