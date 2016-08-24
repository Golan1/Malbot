#include <stdio.h>
#include <windows.h>
#include "Utils.h"
#include "Robot.h"
#include "Eye.h"
#include "Texture2D.h"
#include "Floor.h"

#define FLOOR_SIZE 50.0

GLint winWidth = 600, winHeight = 600;

GLdouble dnear = 0.001, dfar = 1000.0;
GLdouble viewAngle = 50.0;

GLdouble vtheta, vphi;

GLint startX;

Robot* robot;
Eye* eye;
Floor* floorSurface;

GLfloat light1pt[] = { 0.0, 0.1, 0.0, 1.0 };

void drawAxes(GLdouble lineLength) {

	glColor3d(0.0, 1.0, 0.0);

	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, lineLength, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(lineLength, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, lineLength);
	glEnd();

	glColor3d(1.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, -lineLength, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(-lineLength, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, -lineLength);
	glEnd();

	glColor3d(0.0, 0.0, 0.0);

	Utils::print(10, 0, 0, "x", GLUT_BITMAP_TIMES_ROMAN_24);
	Utils::print(0, 10, 0, "y", GLUT_BITMAP_TIMES_ROMAN_24);
	Utils::print(0, 0, 10, "z", GLUT_BITMAP_TIMES_ROMAN_24);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	eye->activate();
	

	GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_POSITION, light1pt);

	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteColor);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.75);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.4);

	glEnable(GL_LIGHT1);
	
	GLfloat globalAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);


	//drawFloor();

	drawAxes(10000.0);

	robot->Draw();

	floorSurface->Draw();

	// For some reason this crashes my computer:
	//glutSwapBuffers();

	glFlush();
}

void myPassiveMotion(int x, int y) {
	int boundry = winWidth - 1;
	const int margin = 15;

	if (x <= margin) {
		x = startX = boundry - 1 - margin;
		glutWarpPointer(x, y);
	}
	else if (x >= boundry - margin) {
		x = startX = margin + 1;
		glutWarpPointer(x, y);
	}

	double deltaX = (startX - x);
	startX = x;
	vphi += deltaX / 3;

	double yPrecentage = y / (double)winHeight;

	vtheta = HEAD_MAX_LOOKING_ANGLE + yPrecentage * (180 - 2 * HEAD_MAX_LOOKING_ANGLE);
}

void setProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, (GLdouble)winWidth / (GLdouble)winHeight, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
}

void myReshape(int width, int height)
{
	winWidth = width;
	winHeight = height;

	glViewport(0, 0, winWidth, winHeight);
	setProjection();
}

void myKeyboard(unsigned char key, int x, int y)
{
	if (key >= 65 && key <= 90) {
		Utils::keys[key - 65] = 1;
	}
	else if (key >= 97 && key <= 122) {
		Utils::keys[key - 97] = 1;
	}

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'c':
	case 'C':
		viewAngle++;
		setProjection();
		break;
	case 'v':
	case 'V':
		viewAngle--;
		setProjection();
		break;
	case 'x':
	case 'X':
		eye->ToggleViewMode();
		break;
	case 'z':
	case 'Z':
		light1pt[1]+= 0.1;
		break;
	default:
		break;
	}
}

void myKeyboardUp(unsigned char key, int x, int y) {
	if (key >= 65 && key <= 90) {
		Utils::keys[key - 65] = 0;
	}
	else if (key >= 97 && key <= 122) {
		Utils::keys[key - 97] = 0;
	}
}

void calcChanges() {
	robot->head->setDirection(vtheta, vphi);
	robot->CalcMovement();

	eye->setDirection(vtheta, vphi);
	eye->setLocation(robot->location);
}

void myTimer(int interval) {
	calcChanges();
	glutPostRedisplay();
	glutTimerFunc(interval, myTimer, interval);
}

void myMouse(int button, int state, int x, int y)
{
	if (button == 3 || button == 4) {

		int direction = button == 3 ? 1 : -1;

		if (Utils::isKeyPressed('q')) {
			robot->ControlUpperArm(direction, Side::Both);
		}

		if (Utils::isKeyPressed('e')) {
			robot->ControlLowerArm(direction, Side::Both);
		}

		if (Utils::isKeyPressed('r')) {
			robot->ControlFist(direction, Side::Both);
		}
	}
	//y = winHeight - y - 1;
}


void generateModels() {

	robot = new Robot();
	robot->Init();

	eye = new Eye();

	floorSurface = new Floor(FLOOR_SIZE);
	floorSurface->Init();
}

void registerCallbacks() {
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	glutPassiveMotionFunc(myPassiveMotion);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyboardUp);
}

void init()
{
	generateModels();

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	startX = cursorPos.x;

	glutSetCursor(GLUT_CURSOR_NONE);

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glutFullScreen();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv)
{
	int windowId;

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	windowId = glutCreateWindow("WOW!");

	init();
	registerCallbacks();
	myTimer(16);
	glutMainLoop();

	return 0;
}

