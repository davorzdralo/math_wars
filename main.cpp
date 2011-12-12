#include <cstdlib>
#include <GL/glut.h>
#include "GameWindow.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Globals.h"

static GameWindow* window;

void gameLoop(int value)
{
	glutTimerFunc(1000 / Globals::FPS, gameLoop, 0);

	window->update();
	window->draw();
}

void display()
{
	// nista
}

void reshape(int screenWidth, int screenHeight)
{
	Globals::screenWidth = screenWidth;
	Globals::screenHeight = screenHeight;

	Globals::viewWidth = Globals::viewHeight * screenWidth / screenHeight;
	
	/* 
	 * Podesimo projekciju. Koristimo ortogonalnu projekciju koja prikazuje deo openGL
	 * "sveta" visine worldHeight, a sirine proporcionalne, odredjeno prema rezoluciji
	 * prozora. Gledamo u pravcu z ose, u pozitivnom smeru, +x je gore, +y desno.
	 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-Globals::viewWidth / 2, Globals::viewWidth / 2, 
		-Globals::viewHeight / 2, Globals::viewHeight / 2, -1.0, 1.0);
	
	// podesimo viewport
	glViewport(0, 0, screenWidth, screenHeight);
//		glViewport(0, 0, 128, 128);
}

void keyboardDown(unsigned char key, int x, int y)
{
	Keyboard::instance()->press(key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	Keyboard::instance()->release(key);
}

void mouseMoved(int x, int y)
{
	Mouse::instance()->setLocation(x, y);
}

int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("GWC");
	glutFullScreen();
	//glutGameModeString("1280x1024:16@60");
	//glutEnterGameMode();

	glutIgnoreKeyRepeat(1);
	glutSetCursor(GLUT_CURSOR_NONE);
	
	window = new GameWindow();

	glutTimerFunc(0, gameLoop, 0); // pokrece glavnu petlju
	glutKeyboardFunc(keyboardDown);
	glutDisplayFunc(display);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(mouseMoved);
	glutPassiveMotionFunc(mouseMoved);
	glutReshapeFunc(reshape);

	// ukljucen blending...
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glClearColor(0.0, 0.0, 0.12, 0.0);

	glutMainLoop();
	return EXIT_SUCCESS;
}

