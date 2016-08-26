#include "Eye.h"



Eye::Eye()
{
	viewMode = ViewMode::thirdPerson;
}


Eye::~Eye()
{
}

void Eye::ToggleViewMode()
{
	switch (viewMode)
	{
	case ViewMode::firstPerson:
		viewMode = ViewMode::fly;
		break;
	case ViewMode::thirdPerson:
		viewMode = ViewMode::firstPerson;
		break;
	case ViewMode::fly:
		viewMode = ViewMode::thirdPerson;
		break;
	default:
		break;
	}
}

void Eye::setDirection(GLfloat vtheta, GLfloat vphi)
{
	GLfloat p = Utils::degToRad(vphi);
	GLfloat t = Utils::degToRad(vtheta);

	direction = { sinf(p), cosf(t), cosf(p) };

	direction.normalize();
}

void Eye::setLocation(Vector3f robotLocation)
{
	switch (viewMode)
	{
	case ViewMode::firstPerson:
	{
		location = robotLocation;
		break;
	}
	case ViewMode::thirdPerson:
	{
		location = { thirdPersonBehindDiff * direction[0], thirdPersonHeightDiff, thirdPersonBehindDiff * direction[2] };
		location += robotLocation;
		break;
	}
	case ViewMode::fly:
	{
		int moveDirection = 0;

		if (Utils::isKeyPressed('w')) {
			moveDirection = 1;
		}
		else if (Utils::isKeyPressed('s')) {
			moveDirection = -1;
		}
		location += moveDirection * direction;
		break;
	}
	default:
		break;
	}
}

void Eye::activate()
{
	Vector3f ref = location + direction;

	gluLookAt(location[0], location[1], location[2], ref[0], ref[1], ref[2], 0.0, 1.0, 0.0);
}
