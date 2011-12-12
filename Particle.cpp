#include "Particle.h"
#include "ResourceCache.h"
#include "Vector.h"
#include "Globals.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include "Explosion.h"

Particle::Particle(const Point& start, Vector direction, const char* textureName)
: ActiveEntity(start, // starting location
               textureName, 
               0.08f, // size
               -90,  // textureAngleOffset, 
               0.1f, // speed
               direction.getAngle(), // starting angle
               0.25f // bounding circle radius
              )
{
	this->direction = direction;
	lenght = 2.0;
	maxSpeed = 0.4;
	minSpeed = 0.1;
	speed = ((double)rand() / RAND_MAX) * (maxSpeed - minSpeed) + minSpeed;
	shorteningRate = 0.04;
}

void Particle::draw() const
{
	//boundingCircle.draw();

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glPushMatrix();
	glTranslatef(location.x, location.y, 0);
	glRotatef(direction.getAngle() +180, 0, 0, 1);
	

	glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);
    {
        glNormal3f(0, 0, 1);
        glTexCoord2f(0, 0); glVertex3f(-size, 0, 0.01);
        glTexCoord2f(0, 1); glVertex3f(-size, -lenght, 0.01);
        glTexCoord2f(1, 1); glVertex3f(size, -lenght, 0.01);
        glTexCoord2f(1, 0); glVertex3f(size, 0, 0.01);
    }
    glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Particle::update()
{
	direction = direction.normalized();
	location.x += direction.getX() * speed;
	location.y += direction.getY() * speed;
	location.z += direction.getZ() * speed;
	boundingCircle.setCenter(location);

	lenght -= shorteningRate;
	if(lenght < 0)
		dead = true;

	bool reversed = false;
	if(location.x < -Globals::worldWidth/2 || location.x > Globals::worldWidth/2)
	{
		direction.setX(direction.getX() * -1);
		reversed = true;
	}
	if(location.y < -Globals::worldHeight/2 || location.y > Globals::worldHeight/2)
	{
		direction.setY(direction.getY() * -1);
		reversed = true;
	}
	
	if(reversed)
	{		
		location.x += direction.getX() * lenght;
		location.y += direction.getY() * lenght;
		location.z += direction.getZ() * lenght;
	}

	if(location.x < -Globals::worldWidth/2)
		location.x = -Globals::worldWidth/2 + lenght;
	
	if(location.x > Globals::worldWidth/2)
		location.x = Globals::worldWidth/2 - lenght;
	
	if(location.y < -Globals::worldHeight/2)
		location.y = -Globals::worldHeight/2 + lenght;
	
	if(location.y > Globals::worldHeight/2)
		location.y = Globals::worldHeight/2 - lenght;
}















