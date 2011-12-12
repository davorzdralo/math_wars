#ifndef _CIRCLE_H_
#define	_CIRCLE_H_

#include <iostream>
#include "Point.h"
#include "Colour.h"

class Circle
{
public:
	Circle(Point center = Point(), double r = 1, Colour colour = Colour(255, 255, 255), 
		bool filled = false, unsigned precision = 24);
	
	void setCenter(Point center);
	void setCenterX(double x);
	void setCenterY(double y);
	void setRadius(double r);
	void setColour(Colour c);
	void setFilled(bool filled);
	void setPrecision(unsigned precision);
	
	const Point& getCenter() const;
	double getRadius() const;
	
	bool intersects(const Circle& other) const;
	void draw() const;
	
	friend std::ostream& operator << (std::ostream& stream, const Circle& circle);
	
private:
	Point center;
	double r;
	Colour colour;
	bool filled;
	unsigned precision;
};

#endif	/* _CIRCLE_H_ */
