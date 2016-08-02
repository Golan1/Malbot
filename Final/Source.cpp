#include <stdio.h>
#include <GL\glut.h>
#include <windows.h>
#include <math.h>
//#include <sstream>

#ifndef PI
#define PI 3.14159265358979323846
#endif

/*  Create checkerboard texture  */
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;
#define FLOOR_LENGTH 50

#define HEAD_MAX_LOOKING_ANGLE 30
#define MOVE_SPEED 0.3
#define TWIST_SPEED 5.0
#define SHOULDER_SPEED 5.0
#define ELBOW_SPEED 3.0
#define MAX_ELBOW_ANGLE 100.0
#define ARM_THICKNESS 0.2
#define FINGER_SPACE 0.05
#define PHALANX_SPACE 0.06
#define MAX_FIST_ANGLE 120.0

GLint winWidth = 600, winHeight = 600;

GLdouble dnear = 0.001, dfar = 1000.0;
GLdouble viewAngle = 50.0;

GLdouble rx = 0.0, ry = 1.0, rz = 0.0;
GLdouble eyex, eyey, eyez;

GLdouble vdirx, vdiry, vdirz;
GLdouble rdirx = 0.0, rdirz = 1.0;

GLdouble vtheta, vphi;

GLdouble upx = 0.0, upy = 1.0, upz = 0.0;

GLint startX;

bool flyMode = false;
bool firstPersonView = true;
GLdouble thirdPersonHeightDiff = 3.0;
GLdouble thirdPersonBehindDiff = 10.0;

GLuint head;
GLdouble headSize[] = { 1.0, 1.0, 1.0 };
GLdouble headTheta, headPhi;

GLuint body;
GLdouble bodySize[] = { 2.0, 1.0, 1.0 };
GLdouble robotAngle = 0.0;

GLuint upperArm;
GLdouble upperArmSize[] = { ARM_THICKNESS, 1.0, ARM_THICKNESS };
GLdouble shoulderAngle = -90;

GLuint elbow;
GLdouble elbowRadius = ARM_THICKNESS / 1.5;

GLuint lowerArm;
GLdouble lowerArmSize[] = { ARM_THICKNESS, 0.7, ARM_THICKNESS };
GLdouble elbowAngle = 90;


GLuint phalanx;
GLdouble phalanxSize[] = { FINGER_SPACE * 2, PHALANX_SPACE * 5, FINGER_SPACE * 2 };
GLdouble fistAngle = 45;

GLuint palm;
GLdouble palmSize[] = { (phalanxSize[0] + FINGER_SPACE) * 5 - FINGER_SPACE, phalanxSize[1] * 3, phalanxSize[2] * 1.5 };

int keys[26];

void glScalefv(GLdouble* arr) {
	glScalef(arr[0], arr[1], arr[2]);
}

GLdouble calcNormal(GLdouble x, GLdouble y, GLdouble z) {
	return sqrt(x * x + y * y + z * z);
}

void print(GLint x, GLint y, GLint z, char *str, void *font)
{
	glRasterPos3i(x, y, z);
	for (char *i = str; *i; i++)
	{
		glutBitmapCharacter(font, *i);
		//glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *i);
	}
}

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
	print(10, 0, 0, "x", GLUT_BITMAP_TIMES_ROMAN_24);
	print(0, 10, 0, "y", GLUT_BITMAP_TIMES_ROMAN_24);
	print(0, 0, 10, "z", GLUT_BITMAP_TIMES_ROMAN_24);
	//print(0, 3, 0, (char *)x, GLUT_BITMAP_TIMES_ROMAN_10);
}

void setCameraPosition() {
	if (!flyMode) {
		eyex = rx, eyey = ry, eyez = rz;
		if (!firstPersonView) {
			GLdouble normal = calcNormal(vdirx, 0, vdirz);
			eyex -= thirdPersonBehindDiff * vdirx / normal;
			eyey += thirdPersonHeightDiff;
			eyez -= thirdPersonBehindDiff * vdirz / normal;
		}
	}

	GLdouble refx = eyex + vdirx;
	GLdouble refy = eyey + vdiry;
	GLdouble refz = eyez + vdirz;

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

void drawPhalanxRow(bool isFirstRow = false) {
	glPushMatrix();

	size_t numOfFingers;

	if (isFirstRow)
	{
		numOfFingers = 3;
		glTranslatef(phalanxSize[0] + FINGER_SPACE, 0, 0);
	}
	else
	{
		numOfFingers = 5;
	}

	for (size_t i = 0; i < numOfFingers; i++)
	{
		glPushMatrix();
		{
			glCallList(phalanx);
		}
		glPopMatrix();

		glTranslatef(phalanxSize[0] + FINGER_SPACE, 0, 0);
	}

	glPopMatrix();
}

void drawHand() {
	glCallList(palm);

	glTranslatef((-palmSize[0] + phalanxSize[0] ) / 2, palmSize[1] + PHALANX_SPACE, 0);
	glRotatef(fistAngle, 1, 0, 0);
	drawPhalanxRow();
	glTranslatef(0, phalanxSize[1] + PHALANX_SPACE, 0);
	glRotatef(fistAngle, 1, 0, 0);
	drawPhalanxRow();
	glTranslatef(0, phalanxSize[1] + PHALANX_SPACE, 0);
	glRotatef(fistAngle, 1, 0, 0);
	drawPhalanxRow(true);
}

void drawArm() {
	// move to the side of the body
	glTranslatef((bodySize[0] + upperArmSize[0]) / 2, 0, 0);

	// rotateShoulder
	glRotatef(shoulderAngle, -1, 0, 0);

	glCallList(upperArm);

	// move to (almost) the end of the upperr arm
	glTranslatef(0, upperArmSize[1] + 0.3 * elbowRadius, 0);
	glCallList(elbow);

	// move to (almost) the end of the elbow
	glPushMatrix();
	{
		glRotatef(elbowAngle, -1, 0, 0);
		glTranslatef(0, elbowRadius * 0.7, 0);
		glCallList(lowerArm);

		glPushMatrix();
		{
			// move to the end of the arm
			glTranslatef(0, lowerArmSize[1], 0);
			glScalef(0.5, 0.5, 0.5);
			drawHand();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void drawRobot() {
	glPointSize(3.0);

	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
	glVertex3f(rx, ry, rz);
	glEnd();

	glPushMatrix();
	{
		// move the robot to its location
		glTranslatef(rx, ry - headSize[1] / 2, rz);

		glPushMatrix();
		{
			// rotate the head accordint to the user's view vector
			glRotatef(headPhi, 0, 1, 0);
			glRotatef(90 - headTheta, -1, 0, 0);

			// draw head
			glCallList(head);

		}
		glPopMatrix();

		glPushMatrix();
		{
			// move the reference point to the middle of the body
			glTranslatef(0, -bodySize[1], 0);

			// rotate the body accordin to the user's wish
			glRotatef(robotAngle, 0, -1, 0);

			print(0, 0, 0, "Malbot", GLUT_BITMAP_TIMES_ROMAN_24);
			// draw the body
			glCallList(body);

			glTranslatef(0, bodySize[1] / 2, 0);

			// draw left arm
			glPushMatrix();
			{
				drawArm();
			}
			glPopMatrix();

			// draw right arm using reflection
			glPushMatrix();
			{
				glScalef(-1, 1, 1);
				drawArm();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setCameraPosition();

	GLfloat whiteColor[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteColor);

	glEnable(GL_LIGHT1);

	GLfloat light1pt[] = { 0.0, 2.0, 0.0, 0.0 };
	//glLightfv(GL_LIGHT1, GL_POSITION, light1pt);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteColor);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, whiteColor);
	//glEnable(GL_LIGHT1);

	drawFloor();

	glEnable(GL_DEPTH_TEST);

	drawAxes(10000.0);

	//glScalef(10.0, 10.0, 10.0);
	//drawHand();
	drawRobot();

	//glutSwapBuffers();

	glFlush();
}

void adjustRobotHeadDirection() {
	headPhi = vphi;
	headTheta = vtheta;
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
	firstPersonView = !firstPersonView;
}

void toggleFlyMode() {
	flyMode = !flyMode;
	adjustRobotHeadDirection();
}

void myKeyboard(unsigned char key, int x, int y) {
	if (key >= 65 && key <= 90) {
		keys[key - 65] = 1;
	}
	else if (key >= 97 && key <= 122) {
		keys[key - 97] = 1;
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
	case 'f':
	case 'F':
		toggleFlyMode();
		break;
	default:
		break;
	}
}

void myKeyboardUp(unsigned char key, int x, int y) {
	if (key >= 65 && key <= 90) {
		keys[key - 65] = 0;
	}
	else if (key >= 97 && key <= 122) {
		keys[key - 97] = 0;
	}

}

void changeLocation(GLdouble x, GLdouble y, GLdouble z) {
	if (flyMode) {
		eyex += x;
		eyey += y;
		eyez += z;
	}
	else {
		rx += x;
		ry += y;
		rz += z;
	}
}

void moveforward(bool backwards = false) {

	GLdouble dirx, diry, dirz;
	if (flyMode) {
		dirx = vdirx;
		diry = vdiry;
		dirz = vdirz;
	}
	else {
		dirx = rdirx;
		diry = 0;
		dirz = rdirz;
	}

	int direction = backwards ? -1 : 1;

	changeLocation(
		dirx * direction * MOVE_SPEED,
		diry * direction * MOVE_SPEED,
		dirz * direction * MOVE_SPEED);

}

void TwistRight(bool left = false) {

	int direction = left ? -1 : 1;

	robotAngle += direction * TWIST_SPEED;
}

double degToRad(double x) {
	return x * PI / 180;
}

bool isKeyPressed(char key) {
	if (key >= 65 && key <= 90) {
		return keys[key - 65];
	}
	else if (key >= 97 && key <= 122) {
		return keys[key - 97];
	}

	return false;
}

void calcDirections() {
	double p = degToRad(vphi);
	double t = degToRad(vtheta);

	vdirx = sin(p);
	vdiry = cos(t);
	vdirz = cos(p);

	GLdouble vdirNormal = calcNormal(vdirx, vdiry, vdirz);
	vdirx /= vdirNormal;
	vdiry /= vdirNormal;
	vdirz /= vdirNormal;

	if (!flyMode) {
		adjustRobotHeadDirection();
	}
}

void calcMovement() {
	if (isKeyPressed('d')) {
		TwistRight();
	}
	if (isKeyPressed('a')) {
		TwistRight(true);
	}

	double a = degToRad(robotAngle + 90);

	rdirx = cos(a);
	rdirz = sin(a);

	GLdouble rdirNormal = calcNormal(rdirx, 0, rdirz);
	rdirx /= rdirNormal;
	rdirz /= rdirNormal;

	if (isKeyPressed('w')) {
		moveforward();
	}
	if (isKeyPressed('s')) {
		moveforward(true);
	}
}

void calcChanges() {
	calcDirections();
	calcMovement();
}

void myTimer(int interval) {
	calcChanges();
	glutPostRedisplay();
	glutTimerFunc(interval, myTimer, interval);
}

void makeCheckImage(void)
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

		if (isKeyPressed('q')) {
			shoulderAngle += direction * SHOULDER_SPEED;
		}

		if (isKeyPressed('e')) {
			elbowAngle += direction * ELBOW_SPEED;
			if (elbowAngle < 0) elbowAngle = 0;
			if (elbowAngle > MAX_ELBOW_ANGLE) elbowAngle = MAX_ELBOW_ANGLE;
		}

		if (isKeyPressed('r')) {
			fistAngle -= direction;
			if (fistAngle < 0) fistAngle = 0;
			if (fistAngle > MAX_FIST_ANGLE) fistAngle = MAX_FIST_ANGLE;
		}
	}
	//y = winHeight - y - 1;
}

void generateCube(GLuint* list, GLdouble* arr, bool isSolid = true) {
	*list = glGenLists(1);
	glNewList(*list, GL_COMPILE);
	glPushMatrix();

	glScalefv(arr);
	glTranslatef(0, 0.5, 0);
	
	isSolid ? glutSolidCube(1.0) : glutWireCube(1.0);

	glPopMatrix();
	glEndList();
}

void generateElbow() {
	elbow = glGenLists(1);
	glNewList(elbow, GL_COMPILE);
	glPushMatrix();

	glutSolidSphere(elbowRadius, 10, 10);

	glPopMatrix();
	glEndList();
}

void generateModels() {
	generateCube(&head, headSize, false);
	generateCube(&body, bodySize);
	generateCube(&upperArm, upperArmSize);
	generateElbow();
	generateCube(&lowerArm, lowerArmSize);
	generateCube(&palm, palmSize);
	generateCube(&phalanx, phalanxSize);

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

void registerCallbacks(void) {
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutReshapeFunc(myReshape);
	glutPassiveMotionFunc(myPassiveMotion);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyboardUp);
}

void init(void)
{
	generateModels();

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	startX = cursorPos.x;

	ry = headSize[1] / 2 + bodySize[1];
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glutFullScreen();

	glutSetCursor(GLUT_CURSOR_NONE);

	//glEnable(GL_LIGHTING);
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

