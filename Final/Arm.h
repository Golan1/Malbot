#pragma once
#include "Sphere.h"
#include "Hand.h"

#define SHOULDER_SPEED 5.0f
#define ELBOW_SPEED 3.0f
#define MAX_ELBOW_ANGLE 150.0f
#define ARM_THICKNESS 0.2f

// Representing a whole robot's arm
class Arm : public Drawable
{
public:
	Arm();
	~Arm();

	void Draw();
	void Init();

	// Fist controling functions
	void ControlFist(int direction);
	void SetFist(GLfloat fistAngle);

	// Upper arm controling functions
	void ControlUpperArm(int direction);
	void SetUpperArm(GLfloat angle);
	
	// Lower arm controling functions
	void ControlLowerArm(int direction);
	void SetLowerArm(GLfloat angle);

private:
	Rect* upperArm;
	Rect* lowerArm;
	Sphere* elbow;
	Hand* hand;

	GLfloat shoulderAngle = 90.0f;
	GLfloat elbowAngle = 90.0f;
};

