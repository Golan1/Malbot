#pragma once
#include "Rect.h"

#define HEAD_MAX_LOOKING_ANGLE 30

class Head :
	public Rect
{
public:
	Head(Vector3d size);
	~Head();

	void Init();
	void Draw();

	void setHeadDirection(GLdouble t, GLdouble p);

	GLdouble theta, phi;
};

