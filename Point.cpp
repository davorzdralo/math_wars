#include "Point.h"
#include "Vector.h"
#include <cmath>

Point::Point(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Point::operator == (const Point& other) const
{
	if(x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

bool Point::operator != (const Point& other) const
{
	return !(*this == other);
}

double Point::distance(const Point& other) const
{
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

Point Point::translate(double x, double y) const
{
	return Point(this->x + x, this->y + y);
}

Point Point::translate(const Vector& v) const
{
	return Point(x + v.getX(), y + v.getY());
}

std::ostream& operator << (std::ostream& stream, const Point& point)
{
	return stream << '<' << point.x << ", " << point.y << ", " << point.z << '>';
}






