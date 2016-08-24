#pragma once
#include "Drawable.h"
#include "Texture2D.h"
class Floor :
	public Drawable
{
public:
	Floor(GLdouble size);
	~Floor();
	void Init();

private:
	GLdouble _size;
	Texture2D* _texture;
};

