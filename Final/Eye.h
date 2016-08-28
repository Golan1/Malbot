#pragma once
#include "Utils.h"

#define BEHIND_ROBOT_LENGTH 2.0f

enum class ViewMode { firstPerson, thirdPerson, fly };

class Eye
{
public:
	Eye();
	~Eye();

	void ToggleViewMode();
	Vector3f GetDirection();
	void SetDirection(GLfloat vtheta, GLfloat vphi);
	void SetLocation(Vector3f robotLocation);
	void Activate();

	inline ViewMode getViewMode(){ return viewMode; }

private:
	ViewMode viewMode;
	Vector3f direction;
	Vector3f location;
};

