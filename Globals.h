#ifndef _GLOBALS_H_
#define	_GLOBALS_H_

#include "Point.h"
#include <GL/glut.h>

class Globals
{
public:
	static const int FPS;

	// velicina ekrana u pikselima
	static int screenWidth;
	static int screenHeight;
	
	// velicina game-worlda u openGL jedinicama koji se slika na ekran
	static const GLdouble viewHeight;
	static GLdouble viewWidth;

	// velicina sveta igre u openGL jedinicama
	static const GLdouble worldWidth;
	static const GLdouble worldHeight;


private:
	Globals()
	{};
};

#endif	/* _GLOBALS_H_ */

