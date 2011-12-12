#include <cstdlib>
#include "Keyboard.h"

Keyboard* Keyboard::_instance = NULL;

Keyboard* Keyboard::instance()
{
    if(Keyboard::_instance == NULL)
        Keyboard::_instance = new Keyboard();
    return Keyboard::_instance;
}

Keyboard::Keyboard()
{  
	for (int i = 0; i < 256; i++)
		keys[i] = false;
}

bool Keyboard::isPressed(unsigned char key) const
{
	return keys[key];
}

void Keyboard::press(unsigned char key)
{
	keys[key] = true;
}

void Keyboard::release(unsigned char key)
{
	keys[key] = false;
}

