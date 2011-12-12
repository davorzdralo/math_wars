#ifndef _GRID_H_
#define	_GRID_H_

#include "Globals.h"
#include "Circle.h"
#include "GridNode.h"
#include <vector>

class GameWindow;

class Grid
{
public:
	Grid(GameWindow* parent);
    void draw() const;
    void update();
    
private:
	std::vector<std::vector<GridNode> > grid;
	GameWindow* parent;
};

#endif	/* _GRID_H_ */


