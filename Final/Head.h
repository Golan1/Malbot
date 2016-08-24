#pragma once
#include "Rect.h"
#include "Sphere.h"

#define HEAD_MAX_LOOKING_ANGLE 30

class Head :
	public Rect
{
public:
	Head(Vector3f size);
	~Head();

	void Init();
	void Draw();

	void setDirection(GLfloat t, GLfloat p);

private:
	GLfloat theta = 0;
	GLfloat phi = 0;
	Sphere* antena;
};

