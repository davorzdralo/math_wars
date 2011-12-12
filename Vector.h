#ifndef _VECTOR_H_
#define	_VECTOR_H_

#include <iostream>
#include "Point.h"

class Vector
{
public:
	Vector();
	Vector(double angle, double norm = 1);
	Vector(double x, double y, double z);
	Vector(Point start, Point end);

	void setX(double x);
	void setY(double y);
	void setZ(double z);
	
	double getX() const;
	double getY() const;
	double getZ() const;
	double getAngle() const;
	
	bool operator == (const Vector& other) const;
    bool operator != (const Vector& other) const;
	Vector operator + (Vector& other);
    
  	friend std::ostream& operator << (std::ostream& stream, const Vector& point);
    
    double norm() const;
    Vector setNorm(double newNorm);
	Vector normalized() const;
private:
	double x;
	double y;
	double z;
};


#endif	/* _VECTOR_H_ */
