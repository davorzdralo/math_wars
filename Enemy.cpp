#include "Enemy.h"
#include "ResourceCache.h"
#include "Utilities.h"
#include "GameWindow.h"

Enemy::Enemy(GameWindow* parent, const Point& location, const char* textureFileName, GLdouble size, 
		GLdouble textureAngleOffset, double speed, double angle, double collisionRadius)
: 	ActiveEntity(location, textureFileName, size, textureAngleOffset, speed, 
		angle, collisionRadius)
{
	rotationPerUpdate = 5;
	this->parent = parent;
}

void Enemy::draw() const
{
	// boundingCircle.draw();

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





