#ifndef _POINT_H_
#define	_POINT_H_

#include <iostream>

class Vector;

class Point
{
public:
	Point(double x = 0, double y = 0, double z = 0);
	void draw() const;
	
	bool operator == (const Point& other) const;
    bool operator != (const Point& other) const;
   	double distance(const Point& other) const;   	

    friend std::ostream& operator << (std::ostream& stream, const Point& point);
    Point translate(double x, double y) const;
    Point translate(const Vector& v) const;

	double x;
	double y;
	double z;
};

#endif	/* _POINT_H_ */

