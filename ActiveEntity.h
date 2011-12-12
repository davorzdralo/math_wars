#ifndef _ACTIVE_ENTITY_H_
#define _ACTIVE_ENTITY_H_

#include "Circle.h"
#include "GameEntity.h"

class ActiveEntity : public GameEntity
{
public:
	ActiveEntity(const Point& location, const char* textureFileName, GLdouble size, 
		GLdouble textureAngleOffset, double speed, double angle, double collisionRadius)
	: GameEntity(location, textureFileName, size, textureAngleOffset), speed(speed), angle(angle), 
		boundingCircle(location, collisionRadius)
	{
		// ovde izgleda nista...
	}

    virtual bool collides(ActiveEntity* other) 
    {
    	return boundingCircle.intersects(other->boundingCircle);
    }

protected:
    double speed;          // maximum movement speed, in game world units per update
   	double angle;          // current angle of entity
    Circle boundingCircle; // circle used for fast (and not necessarily correct) collision checking
};

#endif /* _ACTIVE_ENTITY_H_ */
