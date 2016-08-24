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
	void setLocation(Vector3f robotLocation);
	void activate();

	Vector3f location;
	Vector3f direction;

private:
	ViewMode viewMode;

};

