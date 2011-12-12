#ifndef _GRID_NODE_H_
#define	_GRID_NODE_H_

#include "Point.h"
#include "Colour.h"
#include "Vector.h"
#include "ResourceCache.h"
#include <GL/glut.h>

class GameWindow;

class GridNode
{
public:
	GridNode(Point location = Point(), Colour colour = Colour(0, 0, 150), double size = 0.04);
	void draw() const;
	void update();

	void setLocation(const Point& location);
	void setLocationX(double x);
	void setLocationY(double y);
	void setColour(const Colour& colour);
	void setSize(double size);
	void setEdge(bool edge);
	void setParent(GameWindow* parent);
	
	const Point& getLocation() const;
private:
	void performRepulsions();
	void moveToDefault();
	void clampToPlayArea();
	bool isOnScreen() const;

	Point currentLocation;
	Point defaultLocation;
	Colour currentColour;
	Colour defaultColour;
	double size;
	GameWindow* parent;
	bool edge;
	
	Vector currentMotion;
	double maximumSpeed;
	double maximumSpeedChange;
	// maximum distance to which nodes can move away from their default positions
	double maximumDistanceFromDefault;
	// maximum distance at which nodes are infuenced by projectiles
	double maximumDistanceOfInfluence;
	GLuint textureID;
};

#endif	/* _GRID_NODE_H_ */


