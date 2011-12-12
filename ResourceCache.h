#ifndef _RESOURCE_CACHE_H_
#define _RESOURCE_CACHE_H_

#include <GL/glut.h>
#include "lodepng.h"
#include <vector>
#include <string>

class ResourceCache
{
public:
	static GLuint getTextureID(const char* fileName);
private:
	ResourceCache();
	static ResourceCache* getInstance();
	static ResourceCache* instance;
	GLuint getTexture(const char* fileName);
	std::vector<const char*> keys;
	std::vector<GLuint> values;
};

#endif /* _RESOURCE_CACHE_H_ */
