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

void Eye::SetDirection(GLfloat vtheta, GLfloat vphi)
{
	GLfloat p = Utils::degToRad(vphi);
	GLfloat t = Utils::degToRad(vtheta);

	direction = {sinf(p) * sinf(t), cosf(t), cosf(p) * sinf(t) };

	direction.normalize();
}

void Eye::SetLocation(Vector3f robotLocation)
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
		location = robotLocation - direction * BEHIND_ROBOT_LENGTH;
		if (location[1] < 0.1) location[1] = 0.1;
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

void Eye::Activate()
{
	Vector3f ref = location + direction;

	gluLookAt(location[0], location[1], location[2], ref[0], ref[1], ref[2], 0.0, 1.0, 0.0);
}

Vector3f Eye::GetDirection()
{
	return direction;
}
