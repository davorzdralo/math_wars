#include "Projectile.h"
#include "ResourceCache.h"
#include "Vector.h"
#include "Globals.h"
#include <GL/glut.h>
#include "GameWindow.h"
#include "Explosion.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(GameWindow* parent, const Point& start, Vector direction)
: ActiveEntity(start, // starting location
               "resources/projectile.png", 
               0.5f, // size
               -90,  // textureAngleOffset, 
               0.5f, // speed
               atan2(direction.getY(), direction.getX()) * 180/3.14 + 360, // starting angle
               0.25f // bounding circle radius
              )
{
	this->direction = direction;
	this->parent = parent;
}

Projectile::~Projectile()
{
	Explosion e = Explosion(parent, location, "resources/particle.png", 7, 4);
}

void Projectile::draw() const
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

void Projectile::update()
{
	location.x += direction.getX() * speed;
	location.y += direction.getY() * speed;
	location.z += direction.getZ() * speed;
	boundingCircle.setCenter(location);

	if(location.x < -Globals::worldWidth/2 || location.x > Globals::worldWidth/2 
		|| location.y < -Globals::worldHeight/2 || location.y > Globals::worldHeight/2)
	dead = true;
}

double Projectile::getAngle()
{
	return direction.getAngle();
}

