#include "ResourceCache.h"
#include <iostream>

ResourceCache* ResourceCache::instance = NULL;

ResourceCache* ResourceCache::getInstance()
{
    if(ResourceCache::instance == NULL)
        ResourceCache::instance = new ResourceCache();
    return ResourceCache::instance;
}

ResourceCache::ResourceCache()
{  
	// za sada prazno, treba mi hesh tabela kasnije....
}

GLuint ResourceCache::getTextureID(const char* fileName)
{

	return	getInstance()->getTexture(fileName);

}

GLuint ResourceCache::getTexture(const char* fileName)
{

	bool found = false;

	for(unsigned i = 0; i < keys.size(); i++)
		if(strcmp(keys[i], fileName) == 0)
		{
			found = true;
			break;
		}		
	
	
	if(!found)
	{
		GLuint textureName;
		glGenTextures(1, &textureName);

		std::vector<unsigned char> buffer, image;
	  	LodePNG::loadFile(buffer, fileName); //load the image file with given filename
	  	LodePNG::Decoder decoder;
	  	decoder.decode(image, &buffer[0], (unsigned)buffer.size()); //decode the png

	    glBindTexture(GL_TEXTURE_2D, textureName);

	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	                 decoder.getWidth(), decoder.getHeight(), 0,
	                 GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
                 
		keys.push_back(fileName);
		values.push_back(textureName);
		
	}

	for(unsigned i = 0; i < keys.size(); i++)
		if(strcmp(keys[i], fileName) == 0)
			return values[i];
				

	return -1;
	
	
}


















