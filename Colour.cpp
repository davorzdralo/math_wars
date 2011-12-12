#include "Colour.h"

Colour::Colour(GLubyte r, GLubyte g, GLubyte b)
	: r(r), g(g), b(b)
{
	// nista
}

Colour::Colour()
	: r(0), g(0), b(0)
{
	// nista
}

GLubyte Colour::getRed() const
{
	return r;
}

GLubyte Colour::getGreen() const
{
	return g;
}

GLubyte Colour::getBlue() const
{
	return b;
}

const Colour Colour::red       = Colour(255,   0,   0);
const Colour Colour::white     = Colour(255, 255, 255);
const Colour Colour::black     = Colour(  0,   0,   0);
const Colour Colour::gray      = Colour(170, 170, 170);
const Colour Colour::blue      = Colour(  0,   0, 255);
const Colour Colour::dark_blue = Colour(  0,   0, 128);
const Colour Colour::cyan      = Colour(  0, 255, 255);
const Colour Colour::orange    = Colour(255, 140,   0);
const Colour Colour::yellow    = Colour(255, 255,   0);
const Colour Colour::green     = Colour(  0, 255,   0);
const Colour Colour::magenta   = Colour(160,  32, 240);

