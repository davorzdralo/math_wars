#include "Circle.h"
#include <cmath>
#include <GL/glut.h>
#define PI 3.141

Circle::Circle(Point center, double r, Colour colour, bool filled, unsigned precision)
	: center(center), r(r), colour(colour), filled(filled), precision(precision)
{ 
	/* nista */ 
}

void Circle::setCenter(Point center)
{
	this->center = center;
}

void Circle::setCenterX(double x)
{
	this->center.x = x;
}

void Circle::setCenterY(double y)
{
	this->center.y = y;
}

void Circle::setRadius(double r)
{
	this->r = r;
}
	
const Point& Circle::getCenter() const
{
	return center;
}

double Circle::getRadius() const
{
	return r;
}
	
bool Circle::intersects(const Circle& other) const
{
	return center.distance(other.center) < (r + other.r);
}

void Circle::draw() const
{
	glColor3ub(colour.getRed(), colour.getGreen(), colour.getBlue());
	if(filled)
		glBegin(GL_POLYGON);
	else
		glBegin(GL_LINE_LOOP);
	for(unsigned i = 0; i < precision; i++)
		glVertex2f(cos((double)i / precision * PI * 2) * r + center.x, 
			sin((double)i / precision * PI * 2) * r + center.y);
	glEnd();	
}

void Circle::setColour(Colour colour)
{
	this->colour = colour;
}

void Circle::setFilled(bool filled)
{
	this->filled = filled;
}

void Circle::setPrecision(unsigned precision)
{
	this->precision = precision;
}

std::ostream& operator << (std::ostream& stream, const Circle& circle)
{
	return stream << "[ " << circle.center << ", " << circle.r << " ]";
}


















