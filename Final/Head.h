#pragma once
#include "Rect.h"
#include "Sphere.h"

#define HEAD_MAX_LOOKING_ANGLE 0

// The robot's head
class Head :
	public Rect
{
public:
	Head(Vector3f size);
	~Head();

	void Init();
	void Draw();

	// Set the head direction according to the view direction
	void SetDirection(GLfloat t, GLfloat p);

private:
	GLfloat theta;
	GLfloat phi;
	Sphere* antena;
};

