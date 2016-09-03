#pragma once
#include "Utils.h"

#define BEHIND_ROBOT_LENGTH 2.0f
#define FREE_CAMERA_SPEED 0.3f
#define MIN_CAMERA_ANGLE 30.0f

enum class ViewMode { firstPerson, thirdPerson, light, freeCamera };

// Handling the camera
class Eye
{
public:
	Eye();
	~Eye();

	//  Change between different view modes
	void SwitchViewMode();
	void SetViewMode(ViewMode v);

	// Set the camera's direction
	void SetDirection(GLfloat theta, GLfloat phi);

	// Set the camera's location by an object's position (the robot's for example)
	void SetLocation(Vector3f followObjectLocation);

	// Set the look at transformation
	void Activate();

	inline ViewMode getViewMode(){ return viewMode; }

private:
	ViewMode viewMode;
	Vector3f direction;
	Vector3f location;
};

