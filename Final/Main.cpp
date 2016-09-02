#include <stdio.h>
#include <windows.h>
#include "Robot.h"
#include "Eye.h"
#include "Floor.h"
#include "Light.h"
#include "AnimationManager.h"
#include <string>

// MALBOT = Malben + Robot

#define FLOOR_SIZE 200
#define SIZE_2D 5000
#define AMBIENT_SCALE 100

GLint winWidth, winHeight;

GLfloat dnear = 0.1f, dfar = 300.0f;
GLfloat viewAngle = 50.0f;

GLfloat vtheta, vphi;
GLint startX;

Robot* robot;
Eye* eye;
Floor* floorSurface;
Light* light;
AnimationManager* animationManager;

Texture2D* instructionsTexture;
Material* _instructionsMaterial;

bool isAskingUserForInput = false;
int userInput = 100;

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

void drawTorus() {
	Material::RedRubber.Set();

	glPushMatrix();
	glTranslatef(5.0f, 1.5f, 10.0f);
	glutSolidTorus(0.5, 1.0, 100, 100);
	glPopMatrix();
}

void drawTeapot() {
	Material::Brass.Set();
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 10.0f);
	glutSolidTeapot(1.0);
	glPopMatrix();
}

void drawTetrahedron() {
	Material::Emerald.Set();

	glPushMatrix();
	glTranslatef(-5.0f, 0.0f, 10.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	glutSolidTetrahedron();
	glPopMatrix();
}

void drawInstructions() {
	_instructionsMaterial->Set();

	instructionsTexture->Enable();

	glPushMatrix();
	{
		glTranslatef(0.0f, 0.0f, 15.0f);
		glBegin(GL_QUADS);
		glNormal3fv((-1 * Vector3f::Z_Axis).vec);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(5.0f, 10.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(5.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-5.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-5.0f, 10.0f, 0.0f);
		glEnd();
	}
	glPopMatrix();

	instructionsTexture->Disable();
}

void output(GLfloat x, GLfloat y, char *format, ...)
{
	va_list args;
	char buffer[200], *p;

	va_start(args, format);
	vsprintf_s(buffer, format, args);
	va_end(args);
	glPushMatrix();
	glTranslatef(x, y, 0);
	for (p = buffer; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	glPopMatrix();
}

void drawTexts() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, SIZE_2D, 0, SIZE_2D);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_COLOR_MATERIAL);
	glColor3fv(Light::WhiteColor.vec);

	output(SIZE_2D - 750, 50, "Golan Levi");
	output(50, 50, "Project MALBOT");

	if (!isAskingUserForInput){
		glColor3f(0.0f, 1.0f, 0.0f);
		output(50, SIZE_2D - 150, "Global Ambient Attenuation: %d", userInput);
	}
	else {
		glColor3f(1.0f, 0.0f, 0.0f);
		output(50, SIZE_2D - 150, "Enter value for global ambient attenuation (0-100): %d", userInput);
	}

	glDisable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void myDisplay()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	eye->Activate();

	//drawAxes(10000.0);
	robot->Draw();
	floorSurface->Draw();
	drawTorus();
	drawTeapot();
	drawTetrahedron();
	drawInstructions();

	light->Activate();

	glPopMatrix();

	drawTexts();

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
	glViewport(0, 0, winWidth, winHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, (GLfloat)winWidth / (GLfloat)winHeight, dnear, dfar);
}

void myReshape(int width, int height)
{
	winWidth = width;
	winHeight = height;

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
	case 27: //Escape
		exit(0);
		break;
	case 13: //Enter
		if (isAskingUserForInput) {
			userInput = light->SetGlobalAmbientLight((float)userInput / AMBIENT_SCALE) * AMBIENT_SCALE;
			isAskingUserForInput = false;
		}
		break;
	case 'x':
	case 'X':
		eye->SwitchViewMode();
		break;
	default:
		break;
	}

	if (key >= 48 && key <= 57) {
		int digit = key - 48;

		if (isAskingUserForInput) {
			userInput *= 10;
			userInput += digit;
		}
		else
			animationManager->StartAnimate(digit);
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
	animationManager->Animate();

	eye->SetDirection(vtheta, vphi);

	switch (eye->getViewMode())
	{
	case ViewMode::firstPerson:
	case ViewMode::thirdPerson:
	{
		robot->SetHeadDirection(vtheta, vphi);
		robot->CalcMovement();

		eye->SetLocation(robot->GetLocation());
		break;
	}
	case ViewMode::freeCamera:
		eye->SetLocation(Vector3f::Zero);
		break;
	case ViewMode::light:
	{
		light->SetDirection(vtheta, vphi);
		light->CalcMovement();

		eye->SetLocation(light->GetLocation());
		break;
	}
	default:
		break;
	}
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

		if (Utils::isKeyPressed('t')) {
			light->ControlAtttenuation(direction);
		}

		if (Utils::isKeyPressed('f')) {
			light->ControlFocus(direction);
		}
	}
	//y = winHeight - y - 1;
}

void resetScene() {
	vphi = 0.0f;

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	glutWarpPointer(cursorPos.x, glutGet(GLUT_WINDOW_HEIGHT) * 9.0f / 24.0f);
	startX = cursorPos.x;

	myPassiveMotion(cursorPos.x, glutGet(GLUT_WINDOW_HEIGHT) * 9.0f / 24.0f);

	robot->Reset();
	light->Reset();
	eye->SetViewMode(ViewMode::firstPerson);
}

void generateModels() {

	robot = new Robot();
	robot->Init();

	eye = new Eye();

	floorSurface = new Floor(FLOOR_SIZE);
	floorSurface->Init();

	light = new Light();

	animationManager = new AnimationManager(robot);

	instructionsTexture = new Texture2D("Textures\\instructions.jpg");
	instructionsTexture->Init();

	_instructionsMaterial = new Material(Light::WhiteColor, 0.2f, 1.0f, 0.5f, 50.0f);
	//_teapotMaterial = new Material(Light::WhiteColor, 0.1f, 0.5f, 1.0f, 50.0f);
}

void init()
{
	generateModels();

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.02f);

	glutSetOption(GLUT_MULTISAMPLE, 8);

	glEnable(GL_DEPTH_TEST);

	glutFullScreen();

	glutSetCursor(GLUT_CURSOR_NONE);

	resetScene();
}

void registerCallbacks() {
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	glutPassiveMotionFunc(myPassiveMotion);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyboardUp);
}

void mainMenuActions(int value) {
	switch (value)
	{
	case -1:
		exit(0);
		break;
	case 1:
		userInput = 0;
		isAskingUserForInput = true;
		break;
	case 2:
		resetScene();
		break;
	default:
		break;
	}
}

void viewMenuActions(int value) {
	eye->SetViewMode((ViewMode)value);
}

void createMenus() {
	int viewMain = glutCreateMenu(viewMenuActions);
	glutAddMenuEntry("First Person", (int)ViewMode::firstPerson);
	glutAddMenuEntry("Thrid Person", (int)ViewMode::thirdPerson);
	glutAddMenuEntry("Free Camera", (int)ViewMode::freeCamera);
	glutAddMenuEntry("Light Position", (int)ViewMode::light);


	int main = glutCreateMenu(mainMenuActions);
	glutAddMenuEntry("Adjusting Global Ambient Light", 1);
	glutAddSubMenu("View Mode", viewMain);
	glutAddMenuEntry("Help", 2);
	glutAddMenuEntry("Exit", -1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv)
{
	int windowId;

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	windowId = glutCreateWindow("WOW!");
	createMenus();

	init();
	registerCallbacks();
	myTimer(1000 / FPS);
	glutMainLoop();

	return 0;
}