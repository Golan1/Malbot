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

	// Basic drawing functions
	void Init();
	void Reset();
	void Draw();

	// Twist robot to the side
	void Twist(GLfloat speed, Side side);

	
	void ControlUpperArm(int direction, Side side);
	void SetUpperArm(GLfloat shoulderAngle, Side side);
	
	// Control lower arm functions
	void ControlLowerArm(int direction, Side side);
	void SetLowerArm(GLfloat elbowAngle, Side side);

	// Control fist functions
	void ControlFist(int direction, Side side);
	void SetFist(GLfloat fistAngle, Side side);

	// Control head
	void SetHeadDirection(GLfloat t, GLfloat p);

	// Control movement functions
	void CalcMovement();
	void MoveForward();

	// Get robot locations
	Vector3f GetLocation();

private:
	Head* head;
	Rect* body;
	Arm* leftArm;
	Arm* rightArm;

	GLfloat robotAngle;
	Vector3f direction, location;

	void SetAngle(GLfloat angle);
	static const Vector3f MiddleOfHead;
};

