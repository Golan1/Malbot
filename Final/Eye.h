#pragma once
#include "Utils.h"

#define BEHIND_ROBOT_LENGTH 2.0f
#define FREE_CAMERA_SPEED 0.3f
#define MIN_CAMERA_ANGLE 30.0f

enum class ViewMode { firstPerson, thirdPerson, light, freeCamera };

class Eye
{
public:
	Eye();
	~Eye();

	void SwitchViewMode();
	void SetViewMode(ViewMode v);
	void SetDirection(GLfloat theta, GLfloat phi);
	void SetLocation(Vector3f followObjectLocation);
	void Activate();

	inline ViewMode getViewMode(){ return viewMode; }

private:
	ViewMode viewMode;
	Vector3f direction;
	Vector3f location;
};

