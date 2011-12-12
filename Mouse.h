#ifndef _MOUSE_H_
#define	_MOUSE_H_

#include "Point.h"
#include "GameWindow.h"

class Mouse
{
public:
	static Mouse* instance();
	void setLocation(int x, int y);
	void setViewLocation(const Point& location);
	const Point& getScreenLocation() const;
	const Point& getWorldLocation() const;
	void draw() const;
	
private:
	Mouse();
	void updateWorldLocation();
	
	Point screenLocation;
	Point worldLocation;
	Point viewLocation;
	static Mouse* _instance;
};

#endif	/* _MOUSE_H_ */

