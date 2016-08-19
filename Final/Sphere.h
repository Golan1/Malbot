#pragma once
#include "Drawable.h"
class Sphere :
	public Drawable
{
public:
	Sphere(GLdouble radius);
	~Sphere();

	void Init();
	void Draw();

	GLdouble radius;
private:
};

