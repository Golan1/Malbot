#pragma once
#include "Sphere.h";
#include "Hand.h";

#define SHOULDER_SPEED 5.0
#define ELBOW_SPEED 3.0
#define MAX_ELBOW_ANGLE 100.0
#define ARM_THICKNESS 0.2

class Arm :
	public Drawable
{
public:
	Arm();
	~Arm();

	void Draw();
	void Init();

	void ControlFist(int direction);
	void ControlUpperArm(int direction);
	void ControlLowerArm(int direction);
private:
	Rect* upperArm;
	Rect* lowerArm;
	Sphere* elbow;
	Hand* hand;

	GLdouble shoulderAngle = -90;
	GLdouble elbowAngle = 90;
};

