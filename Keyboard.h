#ifndef _KEYBOARD_H_
#define	_KEYBOARD_H_

class Keyboard
{
public:
	static Keyboard* instance();

	bool isPressed(unsigned char key) const;
	void press(unsigned char key);
	void release(unsigned char key);

private:
	Keyboard();
	bool keys[256];
	static Keyboard* _instance;
};

#endif	/* _KEYBOARD_H_ */

