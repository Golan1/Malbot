#pragma once
#include "Arm.h"
#include "Head.h"
#include "Material.h"

#define MOVE_SPEED 0.1f
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
	void SetUpperArm(GLfloat shoulderAngle, Side side);
	
	void ControlLowerArm(int direction, Side side);
	void SetLowerArm(GLfloat elbowAngle, Side side);

	void ControlFist(int direction, Side side);
	void SetFist(GLfloat fistAngle, Side side);

	void SetHeadDirection(GLfloat t, GLfloat p);
	void CalcMovement();
	void MoveForward();

	Vector3f GetLocation();

	float GetMiddleHeadLocation();

private:
	Head* head;
	Rect* body;
	Arm* leftArm;
	Arm* rightArm;

	GLfloat robotAngle = 0.0;
	Vector3f direction;
	Vector3f location;

	Material* material;
};

