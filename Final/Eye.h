#pragma once
#include "Utils.h"

#define thirdPersonHeightDiff 1.5f
#define thirdPersonBehindDiff -5.0f

enum class ViewMode { firstPerson, thirdPerson, fly };

class Eye
{
public:
	Eye();
	~Eye();

	void ToggleViewMode();
	void setDirection(GLfloat vtheta, GLfloat vphi);
	void setLocation(Vector3f robotLocation);
	void activate();

	Vector3f location;
	Vector3f direction;

	inline ViewMode getViewMode(){ return viewMode; }

private:
	ViewMode viewMode;

};

