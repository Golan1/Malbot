#pragma once
#include "Utils.h"

class Drawable
{
public:
	Drawable();
	~Drawable();
	virtual void Draw();
	virtual void Init() = 0;

protected:
	GLuint _listId;

private:
};

