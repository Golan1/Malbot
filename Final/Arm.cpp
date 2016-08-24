#include "Arm.h"

Arm::Arm()
{
	upperArm = new Rect({ ARM_THICKNESS, 1.0, ARM_THICKNESS });
	lowerArm = new Rect({ ARM_THICKNESS, 0.7, ARM_THICKNESS });
	elbow = new Sphere(ARM_THICKNESS / 1.5);
	hand = new Hand();
}

Arm::~Arm()
{
	delete upperArm;
	delete lowerArm;
	delete elbow;
	delete hand;
}

void Arm::Init()
{
	upperArm->Init();
	lowerArm->Init();
	elbow->Init();
	hand->Init();
}

void Arm::ControlFist(int direction)
{
	hand->ControlFist(direction);
}

void Arm::ControlUpperArm(int direction)
{
	shoulderAngle += direction * SHOULDER_SPEED;
}

void Arm::ControlLowerArm(int direction)
{
	elbowAngle += direction * ELBOW_SPEED;
	if (elbowAngle < 0) elbowAngle = 0;
	if (elbowAngle > MAX_ELBOW_ANGLE) elbowAngle = MAX_ELBOW_ANGLE;
}

void Arm::Draw()
{
	
	// rotateShoulder
	glRotatef(shoulderAngle, -1, 0, 0);

	upperArm->Draw();

	// move to (almost) the end of the upperr arm
	glTranslatef(0, upperArm->size[1] + 0.3 * elbow->radius, 0);
	elbow->Draw();

	// move to (almost) the end of the elbow
	glPushMatrix();
	{
		glRotatef(elbowAngle, -1, 0, 0);
		glTranslatef(0, elbow->radius * 0.7, 0);
		lowerArm->Draw();

		glPushMatrix();
		{
			// move to the end of the arm
			glTranslatef(0, lowerArm->size[1], 0);
			glScalef(0.5, 0.5, 0.5);
			hand->Draw();
		}
		glPopMatrix();
	}
	glPopMatrix();
}
