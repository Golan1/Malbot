#pragma once
#include "Utils.h"

#define thirdPersonHeightDiff 3.0
#define thirdPersonBehindDiff -10.0

enum class ViewMode { firstPerson, thirdPerson };

class Eye
{
public:
	Eye();
	~Eye();

	void ToggleViewMode();
	void setDirection(GLdouble vtheta, GLdouble vphi);
	void setLocation(Vector3d robotLocation);
	void activate();

	Vector3d location;
	Vector3d direction;

private:
	ViewMode viewMode;

};

