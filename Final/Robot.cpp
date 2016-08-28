#include "Robot.h"


Robot::Robot()
{
	head = new Head({ 0.25f, 0.25f, 0.25f });
	body = new Rect({ 0.5f, 0.25f, 0.25f });
	leftArm = new Arm();
	rightArm = new  Arm();

	Vector4f base = { 1.0f, 1.0f, 2.0f, 1.0f };

	material = new Material(0.2f * base, 0.5f * base, 0.3f * base, 100.f);
}


Robot::~Robot()
{
	delete head;
	delete body;
	delete leftArm;
	delete rightArm;
	delete material;
}

void Robot::Init()
{
	head->Init();
	body->Init();
	leftArm->Init();
	rightArm->Init();

	location = { 0.0f, 0.0f, 0.0f };
	direction = { 0.0f, 0.0f, 1.0f };
}

void Robot::Draw()
{
	material->Set();

	glPushMatrix();
	{
		// move the robot to its location
		Utils::glTranslatefv(location.vec);

		glPushMatrix();
		{
			glTranslatef(0, body->size[1], 0);
			head->Draw();
		}
		glPopMatrix();

		glPushMatrix();
		{
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
				glTranslatef((body->size[0] + ARM_THICKNESS / 4) / 2, 0, 0);

				leftArm->Draw();
			}
			glPopMatrix();

			// draw right arm using reflection
			glPushMatrix();
			{
				// reflect to the other side
				glScalef(-1, 1, 1);

				// move to the side of the body
				glTranslatef((body->size[0] + ARM_THICKNESS / 4) / 2, 0, 0);
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

void Robot::SetUpperArm(GLfloat shoulderAngle, Side side)
{
	switch (side)
	{
	case Side::Right:
		rightArm->SetUpperArm(shoulderAngle);
		break;
	case Side::Left:
		leftArm->SetUpperArm(shoulderAngle);
		break;
	default:
		leftArm->SetUpperArm(shoulderAngle);
		rightArm->SetUpperArm(shoulderAngle);
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

void Robot::SetLowerArm(GLfloat elbowAngle, Side side)
{
	switch (side)
	{
	case Side::Right:
		rightArm->SetLowerArm(elbowAngle);
		break;
	case Side::Left:
		leftArm->SetLowerArm(elbowAngle);
		break;
	default:
		leftArm->SetLowerArm(elbowAngle);
		rightArm->SetLowerArm(elbowAngle);
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

void Robot::SetFist(GLfloat fistAngle, Side side)
{
	switch (side)
	{
	case Side::Right:
		rightArm->SetFist(fistAngle);
		break;
	case Side::Left:
		leftArm->SetFist(fistAngle);
		break;
	default:
		leftArm->SetFist(fistAngle);
		rightArm->SetFist(fistAngle);
		break;
	}
}

void Robot::SetHeadDirection(GLfloat t, GLfloat p)
{
	head->SetDirection(t, p);
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

void Robot::MoveForward() {
	location += MOVE_SPEED * direction;
}

Vector3f Robot::GetLocation()
{
	return location;
}

GLfloat Robot::GetMiddleHeadLocation()
{
	return 0.375f;
}
