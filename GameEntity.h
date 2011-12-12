#ifndef _GAME_ENTITY_H_
#define	_GAME_ENTITY_H_

#include "Point.h"
#include "ResourceCache.h"
#include <GL/glut.h>

class GameEntity
{
public:
	GameEntity(const Point& location, const char* textureFileName, GLdouble size, 
		GLdouble textureAngleOffset)
	: location(location), size(size), textureAngleOffset(textureAngleOffset)
	{
		dead = false;
		textureID = ResourceCache::getTextureID(textureFileName);
	}
	
    virtual ~GameEntity() 
    { 
    	/* nista u destruktoru */
    };
    
	bool isDead() const
	{
		return dead;
	};
	
	void setDead(bool dead)
	{
		this->dead = dead;
	};
	
	const Point& getLocation() const
	{
		return location;
	}
	
    virtual void draw() const = 0;
    virtual void update() = 0;


protected:
    Point location;              // current location of entity
    bool dead;                   // current state of entity
   	GLdouble size;               // current size of entity
	GLuint textureID;            // entity's texture ID
	GLdouble textureAngleOffset; // angle by which texture must be rotated to be in "normal" position
};

#endif	/* _GAME_ENTITY_H_ */


