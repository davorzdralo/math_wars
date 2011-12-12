#ifndef _GUI_H_
#define _GUI_H_

class GameWindow;

class GUI
{
public:
	GUI(GameWindow* parent);

	void draw() const;
	void addToHighScore(unsigned additonalPoints);
private:
	void writeText(float x, float y, const char* text, double size, bool centered) const;
	
	GameWindow* parent;
	unsigned highScore;
};

#endif /* _GUI_H_ */
