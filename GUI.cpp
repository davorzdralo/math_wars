#include "GUI.h"
#include <GL/glut.h>
#include <stdlib.h>
#include "ResourceCache.h"
#include "GameWindow.h"
#include "Globals.h"
#include <sstream>

GUI::GUI(GameWindow* parent)
{
	this->parent = parent;
	highScore = 0;
}

void GUI::draw() const
{
	GLuint textureID = ResourceCache::getTextureID("resources/playerIcon.png");
	double size = 1.0;
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
	glPushMatrix();
	glTranslatef(parent->getViewLocation().x, parent->getViewLocation().y, 0);
	glPushMatrix();
	glTranslatef(-size, Globals::viewHeight/2 - size/2, 0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);	
	for(unsigned i = 0; i < parent->getLivesRemaining(); i++)
	{

	    glNormal3f(0, 0, 1);
	    glTexCoord2f(0, 0); glVertex3f(-size + i * size, size, 0.01);
	    glTexCoord2f(0, 1); glVertex3f(-size + i * size, -size, 0.01);
	    glTexCoord2f(1, 1); glVertex3f(size + i * size, -size, 0.01);
	    glTexCoord2f(1, 0); glVertex3f(size + i * size, size, 0.01);
    }
    glEnd();
   	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	

	std::stringstream out;
	out << "SCORE:" << highScore;
	
   	writeText(Globals::viewWidth/2 - 7, 9.3, out.str().c_str(), 5, false);
   	
   	if(parent->getLivesRemaining() == 0)   	
   		writeText(0, 0, "GAME OVER", 10, true);

	glPopMatrix();
}

void GUI::addToHighScore(unsigned additionalPoints)
{
	highScore += additionalPoints;
}

void GUI::writeText(float x, float y, const char* text, double size, bool centered) const
{
	glPushMatrix();
	glColor3f(0.6, 1.0, 0.6); 
	
	if(centered)
		x -= glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, 'a') * strlen(text) * size / 1000 / 2;
		
	glTranslatef(x, y, 0);
	
	glLineWidth(3);
	

	glScalef(size/1000, size/1000, size/1000);

	while(*text != '\0')
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *(text++));
	glPopMatrix();
}

