#include <stdio.h>
#include <windows.h>
#include "Utils.h"
#include "Robot.h"
#include "Eye.h"
#include "Texture2D.h"
#include "Floor.h"

#define FLOOR_SIZE 200
#define FPS 60
GLint winWidth = 600, winHeight = 600;

GLfloat dnear = 0.001f, dfar = 1000.0f;
GLfloat viewAngle = 50.0f;

GLfloat vtheta, vphi;

GLint startX;

Robot* robot;
Eye* eye;
Floor* floorSurface;

Vector4f light1pt = { 0.0f, 5.0f, 0.0f, 1.0f };

void drawAxes(GLfloat lineLength) {

	glColor3f(0.0f, 1.0f, 0.0f);

	(Vector3f::X_Axis * lineLength).drawLine();
	(Vector3f::Y_Axis * lineLength).drawLine();
	(Vector3f::Z_Axis * lineLength).drawLine();

	glColor3f(1.0f, 0.0f, 0.0f);

	(Vector3f::X_Axis * -lineLength).drawLine();
	(Vector3f::Y_Axis * -lineLength).drawLine();
	(Vector3f::Z_Axis * -lineLength).drawLine();

	glColor3f(0.0f, 0.0f, 0.0f);

	Utils::print(FLOOR_SIZE + 1, 0, 0, "x", GLUT_BITMAP_TIMES_ROMAN_24);
	Utils::print(0, 10, 0, "y", GLUT_BITMAP_TIMES_ROMAN_24);
	Utils::print(0, 0, FLOOR_SIZE + 1, "z", GLUT_BITMAP_TIMES_ROMAN_24);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	eye->activate();

	Vector4f white = { 1.0f, 1.0f, 1.0f, 1.0f };
	Vector4f black = { 0.0f, 0.0f, 0.0f, 1.0f };

	//Vector4f ambient = { 0.2f, 0.2f, 0.2f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light1pt.vec);

	glLightfv(GL_LIGHT0, GL_AMBIENT, white.vec);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white.vec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white.vec);

	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

	Vector3f dir = { 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir.vec);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0f);

	glEnable(GL_LIGHT0);

	Vector4f globalAmbient = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient.vec);


	drawAxes(10000.0);

	glBegin(GL_POINTS);
	glVertex3fv(light1pt.vec);
	glEnd();

	robot->Draw();

	floorSurface->Draw();

	// For some reason this crashes my computer:
	//glutSwapBuffers();

	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		printf("\%d", err);
	}

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
	gluPerspective(viewAngle, (GLfloat)winWidth / (GLfloat)winHeight, dnear, dfar);
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
		light1pt[1] += 0.1;
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

	if (eye->getViewMode() != ViewMode::fly) {
		robot->head->setDirection(vtheta, vphi);
		robot->CalcMovement();
	}

	eye->setDirection(vtheta, vphi);

	Vector3f middleHead = { 0.0f, robot->GetMiddleHeadLocation(), 0.0f };

	eye->setLocation(middleHead + robot->location);
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

	glutSetOption(GLUT_MULTISAMPLE, 8);

	glEnable(GL_NORMALIZE);

	//glShadeModel(GL_FLAT);
	//glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv)
{
	int windowId;

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	windowId = glutCreateWindow("WOW!");

	init();
	registerCallbacks();
	myTimer(FPS);
	glutMainLoop();

	return 0;
}

