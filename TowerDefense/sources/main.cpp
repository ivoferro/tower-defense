#include <stdlib.h>
#include <GL/glut.h>
#include "../headers/framework/Application.h"
#include "../headers/framework/State.h"

// Callback to reshape window
void Reshape(int width, int height)
{
	Application::instance()->getSceneManager()->activeScene()->Reshape(width, height);
}

// Callback to draw objects
void Draw(void)
{
	Application::instance()->getSceneManager()->activeScene()->Draw();
}

// Callback for timer actions (e.g. animations)
void Timer(int value)
{
	glutTimerFunc(Application::instance()->getState()->getMovementDelay(), Timer, 0);
	Application::instance()->getSceneManager()->activeScene()->Timer(value);
	glutPostRedisplay();
}

// Callback to interact via keyboard (press a key)
void Key(unsigned char key, int x, int y)
{
	Application::instance()->getSceneManager()->activeScene()->Key(key, x, y);
}

// Callback to interact via keyboard (release a key)
void KeyUp(unsigned char key, int x, int y)
{
	Application::instance()->getSceneManager()->activeScene()->KeyUp(key, x, y);
}

// Callback to interact via special keys (press a key)
void SpecialKey(int key, int x, int y)
{
	Application::instance()->getSceneManager()->activeScene()->SpecialKey(key, x, y);
}

// Callback to interact via special keys (release a key)
void SpecialKeyUp(int key, int x, int y)
{
	Application::instance()->getSceneManager()->activeScene()->SpecialKeyUp(key, x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(
		((Application::instance()->getState()->isDoubleBufferActivated()) 
		? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB | GLUT_DEPTH);
	if (glutCreateWindow("Tower Defense") == GL_FALSE)
		exit(1);

	Application::instance()->getSceneManager()->activeScene()->Init();

	// Register GLUT Callbacks

	// Window/Drawing Callbacks
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Draw);

	// Keyboard Callbacks
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(SpecialKey);
	glutSpecialUpFunc(SpecialKeyUp);

	// timer/idle callbacks
	glutTimerFunc(Application::instance()->getState()->getMovementDelay(), Timer, 0);

	// BEGIN...
	glutMainLoop();
	return 0;
}