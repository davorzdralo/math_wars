#ifndef _COLOUR_H_
#define	_COLOUR_H_

#include <GL/glut.h>

class Colour
{
public:
	Colour(GLubyte r, GLubyte b, GLubyte g);
	Colour();

	GLubyte getRed() const;
	GLubyte getGreen() const;
	GLubyte getBlue() const;

    const static Colour white;
    const static Colour gray;
    const static Colour black;
    const static Colour red;
    const static Colour green;
    const static Colour blue;
    const static Colour dark_blue;
    const static Colour cyan;
    const static Colour orange;
    const static Colour yellow;
    const static Colour magenta;
    
private:
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

#endif	/* _COLOUR_H_ */

