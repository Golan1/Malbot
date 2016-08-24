#pragma once
#include "Arm.h"
#include "Head.h"

#define MOVE_SPEED 0.3
#define TWIST_SPEED 5.0

enum  class Side { Both , Right, Left };

class Robot : public Drawable
{
public:
	Robot();
	~Robot();

	void Init();
	void Draw();

	void Twist(Side side);
	void ControlUpperArm(int direction, Side side);
	void ControlLowerArm(int direction, Side side);
	void ControlFist(int direction, Side side);

	void CalcMovement();

	Vector3d location;
	Head* head;

private:
	Rect* body;
	Arm* leftArm;
	Arm* rightArm;

	GLdouble robotAngle = 0.0;
	Vector3d direction;
};

