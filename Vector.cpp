#include "Vector.h"
#include <cmath>

Vector::Vector()
	: x(0), y(0), z(0)
{
	// ...
}

Vector::Vector(double angle, double norm)
{
	angle -= 90;
	x = cos(angle / 180 * 3.14159265) * norm;
	y = sin(angle / 180 * 3.14159265) * norm;
	z = 0;
}

Vector::Vector(double x, double y, double z)
	: x(x), y(y), z(z)
{
	// ...
}

Vector::Vector(Point start, Point end)
	: x(end.x - start.x), y(end.y - start.y), z(end.z - start.z)
{
	// ...
}
	
void Vector::setX(double x)
{	
	this->x = x;
}

void Vector::setY(double y)
{
	this->y = y;  
}
void Vector::setZ(double z)
{
	this->z = z;  
}

double Vector::getX() const
{
	return x;
}

double Vector::getY() const
{
	return y;
}

double Vector::getZ() const
{
	return z;
}

double Vector::getAngle() const
{
	return atan2(y, x) / 3.14159265 * 180 + 90;
}

bool Vector::operator == (const Vector& other) const
{
	// treba koristiti neko episilon za jednakost realnih brojeva...
	if(x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

bool Vector::operator != (const Vector& other) const
{
	return !(*this == other);
}

Vector Vector::operator + (Vector& other)
{
	return Vector(x + other.x, y + other.y, 0);
}

std::ostream& operator << (std::ostream& stream, const Vector& vector)
{
	return stream << '[' << vector.x << ", " << vector.y << ", " << vector.z << ']' ;
}

// vraca normu vektora
double Vector::norm() const
{
	if(x == 0 && y == 0 && z == 0)
		return 0;
	else
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

// blago retardirana funkcija, ali potrebna za program....
Vector Vector::setNorm(double newNorm)
{
	if(norm() == 0)
		return Vector(0, 0, 0);
	else
		return Vector(x / norm() * newNorm, y / norm() * newNorm, z / norm() * newNorm);
}

// vraca normalizovan vektor
Vector Vector::normalized() const
{
	if(norm() == 0)
		return Vector(0, 0, 0);
	else
		return Vector(x / norm(), y / norm(), z / norm());
}




