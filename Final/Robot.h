#pragma once
#include "Arm.h"
#include "Head.h"
#include "Material.h"

#define MOVE_SPEED 0.3f
#define TWIST_SPEED 5.0f

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

	float GetMiddleHeadLocation();

	Vector3f location;
	Head* head;

private:
	Rect* body;
	Arm* leftArm;
	Arm* rightArm;

	GLfloat robotAngle = 0.0;
	Vector3f direction;

	Material* material;
};

