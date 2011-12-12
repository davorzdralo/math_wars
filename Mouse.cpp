#include <cstdlib>
#include <iostream>
#include "Mouse.h"
#include "Globals.h"

Mouse* Mouse::_instance = NULL;

Mouse* Mouse::instance()
{
    if(Mouse::_instance == NULL)
        Mouse::_instance = new Mouse();
    return Mouse::_instance;
}

Mouse::Mouse()
{  
	// pft
}

void Mouse::setViewLocation(const Point& location)
{
	viewLocation = location;
	
	updateWorldLocation();
}

void Mouse::setLocation(int x, int y)
{
	screenLocation.x = x;
	screenLocation.y = y;
	
	updateWorldLocation();
}

void Mouse::updateWorldLocation()
{
	// transformacija iz ekranskih koordinata u game-world koordinate
	worldLocation.x = screenLocation.x * Globals::viewWidth / Globals::screenWidth 
		- Globals::viewWidth/2 + viewLocation.x;
	worldLocation.y = -(screenLocation.y * Globals::viewHeight / Globals::screenHeight 
		- Globals::viewHeight/2) + viewLocation.y;
}

const Point& Mouse::getScreenLocation() const
{
	return screenLocation;
}

const Point& Mouse::getWorldLocation() const
{
	return worldLocation;
}	
	
void Mouse::draw() const
{
	double size = 0.7;
	static GLuint textureID = ResourceCache::getTextureID("resources/whitecircle.png");

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glPushMatrix();
	glTranslatef(worldLocation.x, worldLocation.y, 0);
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
	
	
	
	
	

