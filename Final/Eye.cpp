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
		viewMode = ViewMode::thirdPerson;
		break;
	case ViewMode::thirdPerson:
		viewMode = ViewMode::firstPerson;
		break;
	default:
		break;
	}
}

void Eye::setDirection(GLdouble vtheta, GLdouble vphi)
{
	GLdouble p = Utils::degToRad(vphi);
	GLdouble t = Utils::degToRad(vtheta);

	direction = { sin(p), cos(t), cos(p) };

	direction.normalize();
}

void Eye::setLocation(Vector3f robotLocation)
{
	switch (viewMode)
	{
	case ViewMode::firstPerson:
		location = robotLocation;
		break;
	case ViewMode::thirdPerson:
		location = { thirdPersonBehindDiff * direction[0], thirdPersonHeightDiff, thirdPersonBehindDiff * direction[2]};
		location += robotLocation;
		break;
	default:
		break;
	}
}

void Eye::activate()
{
	Vector3f ref = location + direction;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(location[0], location[1], location[2], ref[0], ref[1], ref[2], 0.0, 1.0, 0.0);
}
