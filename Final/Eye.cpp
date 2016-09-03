#include "Eye.h"

Eye::Eye()
{
	viewMode = ViewMode::firstPerson;
}

Eye::~Eye()
{
}

void Eye::SwitchViewMode()
{
	switch (viewMode)
	{
	case ViewMode::firstPerson:
		viewMode = ViewMode::thirdPerson;
		break;
	case ViewMode::thirdPerson:
		viewMode = ViewMode::freeCamera;
		break;
	case ViewMode::freeCamera:
		viewMode = ViewMode::light;
		break;
	case ViewMode::light:
		viewMode = ViewMode::firstPerson;
		break;
	default:
		break;
	}
}

void Eye::SetViewMode(ViewMode v) {
	viewMode = v;
}

void Eye::SetDirection(GLfloat theta, GLfloat phi)
{
	if (theta < MIN_CAMERA_ANGLE) theta = MIN_CAMERA_ANGLE;

	direction = Utils::getDirectionVector(theta, phi);
}

void Eye::SetLocation(Vector3f followObjectLocation)
{
	switch (viewMode)
	{
	case ViewMode::firstPerson:
	{
		location = followObjectLocation;
		break;
	}
	case ViewMode::thirdPerson:
	case ViewMode::light:
	{
		location = followObjectLocation - direction * BEHIND_ROBOT_LENGTH;
		if (location[1] < 0.1f) location[1] = 0.1f;
		break;
	}
	case ViewMode::freeCamera:
	{
		int moveDirection = 0;

		if (Utils::isKeyPressed('w')) {
			moveDirection = 1;
		}
		else if (Utils::isKeyPressed('s')) {
			moveDirection = -1;
		}
		location += moveDirection * direction * FREE_CAMERA_SPEED;

		if (location[1] < 0.1f) location[1] = 0.1f;

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
