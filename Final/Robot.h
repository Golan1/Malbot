#pragma once
#include "Arm.h"
#include "Head.h"
#include "Material.h"

#define MOVE_SPEED 0.1f
#define TWIST_SPEED 5.0f

class Robot : public Drawable
{
public:
	Robot();
	~Robot();

	void Init();
	void Reset();
	void Draw();

	void Twist(GLfloat speed, Side side);

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


private:
	Head* head;
	Rect* body;
	Arm* leftArm;
	Arm* rightArm;

	GLfloat robotAngle;
	Vector3f direction;
	Vector3f location;

	void SetAngle(GLfloat angle);
	static const Vector3f MiddleOfHead;
};

