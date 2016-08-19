#include "Robot.h"
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "Utils.h"
//#include <sstream>

enum class ViewMode { firstPerson, thirdPerson };

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;
#define FLOOR_LENGTH 50

ViewMode viewMode;

GLint winWidth = 600, winHeight = 600;

GLdouble dnear = 0.001, dfar = 1000.0;
GLdouble viewAngle = 50.0;

GLdouble eyex, eyey, eyez;

Vector3d viewDirection;

GLdouble vtheta, vphi;

GLdouble upx = 0.0, upy = 1.0, upz = 0.0;

GLint startX;

GLdouble thirdPersonHeightDiff = 3.0;
GLdouble thirdPersonBehindDiff = 10.0;

Robot* robot;

void drawAxes(GLdouble lineLength) {

	glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, lineLength, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(lineLength, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, lineLength);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, -lineLength, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-lineLength, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -lineLength);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);

	/*std::ostringstream strs;
	strs << phi;
	std::string str = strs.str();
	const char* x = str.c_str();
	*/
	Utils::print(10, 0, 0, "x", GLUT_BITMAP_TIMES_ROMAN_24);
	Utils::print(0, 10, 0, "y", GLUT_BITMAP_TIMES_ROMAN_24);
	Utils::print(0, 0, 10, "z", GLUT_BITMAP_TIMES_ROMAN_24);
	//print(0, 3, 0, (char *)x, GLUT_BITMAP_TIMES_ROMAN_10);
}

void setCameraPosition() {
	eyex = robot->location[0];
	eyey = robot->location[1];
	eyez = robot->location[2];

	if (viewMode == ViewMode::thirdPerson) {
		GLdouble normal = Utils::calcNormal(viewDirection);
		eyex -= thirdPersonBehindDiff * viewDirection[0] / normal;
		eyey += thirdPersonHeightDiff;
		eyez -= thirdPersonBehindDiff * viewDirection[2] / normal;
	}

	GLdouble refx = eyex + viewDirection[0];
	GLdouble refy = eyey + viewDirection[1];
	GLdouble refz = eyez + viewDirection[2];

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, refx, refy, refz, upx, upy, upz);
}

void drawFloor() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-FLOOR_LENGTH, -0.1, -FLOOR_LENGTH);
	glTexCoord2f(0.0, 1.0); glVertex3f(-FLOOR_LENGTH, -0.1, FLOOR_LENGTH);
	glTexCoord2f(1.0, 1.0); glVertex3f(FLOOR_LENGTH, -0.1, FLOOR_LENGTH);
	glTexCoord2f(1.0, 0.0); glVertex3f(FLOOR_LENGTH, -0.1, -FLOOR_LENGTH);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setCameraPosition();

	GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 };


	//glEnable(GL_LIGHT1);

	GLfloat light1pt[] = { 0.0, 2.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light1pt);
	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteColor);
	glEnable(GL_LIGHT1);

	drawFloor();

	drawAxes(10000.0);

	//glScalef(10.0, 10.0, 10.0);
	robot->Draw();

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

void toggleFirstThirdView() {
	switch (viewMode)
	{
	case ViewMode::firstPerson:
		viewMode = ViewMode::thirdPerson;
		break;
	case ViewMode::thirdPerson:
		viewMode = ViewMode::firstPerson;
		break;
	default:
		break;
	}
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
		toggleFirstThirdView();
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

void calcDirections() {
	double p = Utils::degToRad(vphi);
	double t = Utils::degToRad(vtheta);

	viewDirection = { sin(p), cos(t), cos(p) };

	Utils::normalize(viewDirection);

	//if (!flyMode) {
	robot->head->setHeadDirection(vtheta, vphi);
	//}
}

void calcChanges() {
	calcDirections();
	robot->CalcMovement();
}

void myTimer(int interval) {
	calcChanges();
	glutPostRedisplay();
	glutTimerFunc(interval, myTimer, interval);
}

void makeCheckImage()
{
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}
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
	makeCheckImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
		GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
		checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		checkImage);
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

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glutFullScreen();

	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
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

