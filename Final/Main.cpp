#include <stdio.h>
#include <windows.h>
#include "Robot.h"
#include "Eye.h"
#include "Floor.h"
#include "Light.h"
#include "AnimationManager.h"

#define FLOOR_SIZE 200

GLint winWidth, winHeight;

GLfloat dnear = 0.001f, dfar = 1000.0f;
GLfloat viewAngle = 50.0f;

GLfloat vtheta, vphi;
GLint startX;

Robot* robot;
Eye* eye;
Floor* floorSurface;
Light* light;
AnimationManager* animationManager;

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

	eye->Activate();

	//drawAxes(10000.0);

	robot->Draw();

	floorSurface->Draw();

	light->Activate();

	// For some reason this crashes my computer
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

	vphi += (startX - x) / 3.0f;
	startX = x;

	vtheta = y / (GLfloat)winHeight * 180;
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

	if (key >= 48 && key <= 57) {
		animationManager->StartAnimate(key - 48);
	}

	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'x':
	case 'X':
		eye->ToggleViewMode();
		break;
	case 'z':
	case 'Z':
		//light1pt[1] += 0.1;
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
		robot->SetHeadDirection(vtheta, vphi);
		robot->CalcMovement();
	}

	eye->SetDirection(vtheta, vphi);

	Vector3f middleHead = { 0.0f, robot->GetMiddleHeadLocation(), 0.0f };

	eye->SetLocation(middleHead + robot->GetLocation());

	light->SetDirection(eye->GetDirection());
	light->CalcMovement();

	animationManager->Animate();
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

	light = new Light({ 0.0f, 15.0f, 0.0f, 1.0f }, { 0.0f, -0.1f, 0.0f });

	animationManager = new AnimationManager(robot);
}

void init()
{
	generateModels();

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	startX = cursorPos.x;

	glutSetCursor(GLUT_CURSOR_NONE);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	glutFullScreen();

	glEnable(GL_DEPTH_TEST);

	glutSetOption(GLUT_MULTISAMPLE, 8);

	glEnable(GL_LIGHTING);

	glEnable(GL_NORMALIZE);
}

void registerCallbacks() {
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	glutPassiveMotionFunc(myPassiveMotion);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyboardUp);
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
	myTimer(1000 / FPS);
	glutMainLoop();

	return 0;
}

