#pragma once
#include "Drawable.h"

// Basic sphere
class Sphere :
	public Drawable
{
public:
	Sphere(GLfloat radius);
	~Sphere();

	void Init();
	void Draw();

	GLfloat radius;
private:
};

