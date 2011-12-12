#include "Grid.h"
#include <GL/glut.h>
#include <iostream>
#include "Utilities.h"

Grid::Grid(GameWindow* parent)
{
	this->parent = parent;
	
	int gridWidth = Globals::worldWidth + 30 + 1;
	int gridHeight = Globals::worldHeight + 20 + 1;
	
	grid.resize(gridWidth);
	for(unsigned i = 0; i < grid.size(); i++)
		grid[i].resize(gridHeight);
		

	for(unsigned i = 0; i < grid.size(); i++) // kroz redove
	{
		for(unsigned j = 0; j < grid[i].size(); j++) // kroz kolone
		{
			if(i == 0 || j == 0 || i == (unsigned)(gridWidth-1) || j == (unsigned)(gridHeight-1))
				grid[i][j].setEdge(true);
			if(i%5 == 0 or j%5 == 0)
				grid[i][j].setSize(0.13);
			else
				grid[i][j].setSize(0.06);
			grid[i][j].setParent(parent);
			grid[i][j].setLocationX((double) i * (Globals::worldWidth/(gridWidth-1)) - Globals::worldWidth/2);
			grid[i][j].setLocationY((double) j * (Globals::worldHeight/(gridHeight-1)) - Globals::worldHeight/2);
		}
	}
}

void Grid::draw() const
{

//*

	glLineWidth(7);
	glColor4ub(0, 0, 250, 30);
	glBegin(GL_LINES);
	{	
		// crtamo deblje vertikalne linije
		for(unsigned i = 0; i < grid.size(); i++)
		{
			for(unsigned j = 0; j < grid[i].size() - 1; j++)
			{				
				glVertexp(grid[i][j].getLocation());
				glVertexp(grid[i][j+1].getLocation());
			}
		}		
	}
	glEnd();

	glLineWidth(1);	
	glColor4ub(0, 0, 250, 70);
	glBegin(GL_LINES);
	{	
		// crtamo tanje vertikalne linije
		for(unsigned i = 0; i < grid.size(); i++)
		{
			for(unsigned j = 0; j < grid[i].size() - 1; j++)
			{
				glVertexp(grid[i][j].getLocation());
				glVertexp(grid[i][j+1].getLocation());
			}
		}
	}
	glEnd();
	
	glLineWidth(7);
	glColor4ub(0, 0, 250, 30);
	glBegin(GL_LINES);
	{	
		// crtamo horizontalne linije
		for(unsigned j = 0; j < grid[0].size(); j++)
		{
			for(unsigned i = 0; i < grid.size()-1; i++)
			{
			
				glVertexp(grid[i][j].getLocation());
				glVertexp(grid[i+1][j].getLocation());
			}
		}
	}
	glEnd();
	
	glLineWidth(1);
	glColor4ub(0, 0, 250, 70);
	glBegin(GL_LINES);
	{	
		// crtamo horizontalne linije
		for(unsigned j = 0; j < grid[0].size(); j++)
		{
			for(unsigned i = 0; i < grid.size()-1; i++)
			{
				glVertexp(grid[i][j].getLocation());
				glVertexp(grid[i+1][j].getLocation());
			}
		}
	}
	glEnd();

//*/
	// crtamo spoljnu ivicu	
	glBegin(GL_QUADS);
	{		
		glColor3ub(0, 0, 150);
		GLdouble margin = 0.2;
		
		glVertex2d( Globals::worldWidth/2,          -Globals::worldHeight/2 - margin);
		glVertex2d( Globals::worldWidth/2,           Globals::worldHeight/2 + margin);
		glVertex2d( Globals::worldWidth/2 + margin,  Globals::worldHeight/2 + margin);
		glVertex2d( Globals::worldWidth/2 + margin, -Globals::worldHeight/2 - margin);
		
		glVertex2d(-Globals::worldWidth/2,          -Globals::worldHeight/2 - margin);
		glVertex2d(-Globals::worldWidth/2,           Globals::worldHeight/2 + margin);
		glVertex2d(-Globals::worldWidth/2 - margin,  Globals::worldHeight/2 + margin);
		glVertex2d(-Globals::worldWidth/2 - margin, -Globals::worldHeight/2 - margin);

		
		glVertex2d(-Globals::worldWidth/2, -Globals::worldHeight/2 - margin);
		glVertex2d( Globals::worldWidth/2, -Globals::worldHeight/2 - margin);
		glVertex2d( Globals::worldWidth/2, -Globals::worldHeight/2);
		glVertex2d(-Globals::worldWidth/2, -Globals::worldHeight/2);
		
		glVertex2d( Globals::worldWidth/2,  Globals::worldHeight/2 + margin);
		glVertex2d(-Globals::worldWidth/2,  Globals::worldHeight/2 + margin);	
		glVertex2d(-Globals::worldWidth/2,  Globals::worldHeight/2);	
		glVertex2d( Globals::worldWidth/2,  Globals::worldHeight/2);
	}
	glEnd();
	
	// crtamo cvorove mreze
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	for(unsigned i = 0; i < grid.size(); i++)
		for(unsigned j = 0; j < grid[i].size(); j++)
			grid[i][j].draw();
	glDisable(GL_TEXTURE_2D);
}

void Grid::update()
{
	for(unsigned i = 0; i < grid.size(); i++)
	{
		for(unsigned j = 0; j < grid[i].size(); j++)
		{
			grid[i][j].update();
		}
	}
}



















