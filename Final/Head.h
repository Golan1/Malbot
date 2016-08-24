#pragma once
#include "Rect.h"
#include "Sphere.h"

#define HEAD_MAX_LOOKING_ANGLE 30

class Head :
	public Rect
{
public:
	Head(Vector3d size);
	~Head();

	void Init();
	void Draw();

	void setDirection(GLdouble t, GLdouble p);

private:
	GLdouble theta = 0;
	GLdouble phi = 0;
	Sphere* antena;
};

