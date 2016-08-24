#include "Robot.h"


Robot::Robot()
{
	head = new Head({ 1.0, 1.0, 1.0 });
	body = new Rect({ 2.0, 1.0, 1.0 });
	leftArm = new Arm();
	rightArm = new  Arm();
}


Robot::~Robot()
{
	delete head;
	delete body;
	delete leftArm;
	delete rightArm;
}

void Robot::Init()
{
	head->Init();
	body->Init();
	leftArm->Init();
	rightArm->Init();

	location = { 0.0, head->size[1] / 2 + body->size[1], 0.0 };
	direction = { 0.0, 0.0, 1.0 };
}

void Robot::Draw()
{

	glPointSize(3.0);

	Vector3f whiteColor = { 0.5, 0.5, 0.5 };
	//glColor3d(0.0, 0.0, 1.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, whiteColor.vec);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteColor.vec);
	glMaterialfv(GL_FRONT, GL_SPECULAR, whiteColor.vec);


	glBegin(GL_POINTS);
	glVertex3fv(location.vec);
	glEnd();

	glPushMatrix();
	{
		// move the robot to its location
		glTranslatef(location[0], location[1] - head->size[1] / 2, location[2]);

		head->Draw();

		glPushMatrix();
		{
			// move the reference point to the middle of the body
			glTranslatef(0, -body->size[1], 0);

			// rotate the body accordin to the user's wish
			glRotatef(robotAngle, 0, -1, 0);

			//Utils::print(0, 0, 0, "Malbot", GLUT_BITMAP_TIMES_ROMAN_24);
			// draw the body
			body->Draw();

			glTranslatef(0, body->size[1] / 2, 0);

			// draw left arm
			glPushMatrix();
			{
				// move to the side of the body
				glTranslatef((body->size[0] + ARM_THICKNESS) / 2, 0, 0);
				leftArm->Draw();
			}
			glPopMatrix();

			// draw right arm using reflection
			glPushMatrix();
			{
				glScalef(-1, 1, 1);
				// move to the side of the body
				glTranslatef((body->size[0] + ARM_THICKNESS) / 2, 0, 0);
				rightArm->Draw();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Robot::Twist(Side side)
{
	int direction = 0;
	switch (side)
	{
	case Side::Right:
		direction = 1;
		break;
	case Side::Left:
		direction = -1;
		break;
	default:
		break;
	}

	robotAngle += direction * TWIST_SPEED;
}

void Robot::ControlUpperArm(int direction, Side side)
{
	switch (side)
	{
	case Side::Right:
		rightArm->ControlUpperArm(direction);
		break;
	case Side::Left:
		leftArm->ControlUpperArm(direction);
		break;
	default:
		leftArm->ControlUpperArm(direction);
		rightArm->ControlUpperArm(direction);
		break;
	}
}

void Robot::ControlLowerArm(int direction, Side side)
{
	switch (side)
	{
	case Side::Right:
		rightArm->ControlLowerArm(direction);
		break;
	case Side::Left:
		leftArm->ControlLowerArm(direction);
		break;
	default:
		leftArm->ControlLowerArm(direction);
		rightArm->ControlLowerArm(direction);
		break;
	}
}

void Robot::ControlFist(int direction, Side side)
{
	switch (side)
	{
	case Side::Right:
		rightArm->ControlFist(direction);
		break;
	case Side::Left:
		leftArm->ControlFist(direction);
		break;
	default:
		leftArm->ControlFist(direction);
		rightArm->ControlFist(direction);
		break;
	}
}

void Robot::CalcMovement()
{
	if (Utils::isKeyPressed('d')) {
		Twist(Side::Right);
	}
	else if (Utils::isKeyPressed('a')) {
		Twist(Side::Left);
	}

	GLfloat a = Utils::degToRad(robotAngle + 90);

	direction = { cosf(a), 0.f, sinf(a) };

	direction.normalize();

	int moveDirection = 0;

	if (Utils::isKeyPressed('w')) {
		moveDirection = 1;
	}
	else if (Utils::isKeyPressed('s')) {
		moveDirection = -1;
	}

	location += moveDirection * MOVE_SPEED * direction;
}

