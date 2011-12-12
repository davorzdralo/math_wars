#include "Utilities.h"
#include <GL/glut.h>

void glVertexp(Point point)
{
	glVertex3d(point.x, point.y, point.z);
}





/*

GLuint EmptyTexture()							// Create An Empty Texture
{
	GLuint txtnumber;						// Texture ID
	unsigned int* data;						// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*) new GLuint[((128 * 128)* 4 * sizeof(unsigned int))];		
	// After allocating space we zero it using the ZeroMemory function, passing the pointer (data) and the size of memory to be "zeroed". 

	// A semi important thing to note is that we set the magnification and minification methods to GL_LINEAR. That's because we will be stretching our texture and GL_NEAREST looks quite bad if stretched. 	
		

	ZeroMemory(data,((128 * 128)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);					// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);			// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 128, 128, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);			// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;							// Release data

	return txtnumber;						// Return The Texture ID
}*/


