#pragma once
#include "Utils.h"

// Abstract function that all objects that want to be drawn need to inherit from
// Not so usefull but got a future potential if the main proccess will just hold an array of Drawables.
class Drawable
{
public:
	Drawable();
	~Drawable();
	virtual void Draw();
	virtual void Init() = 0;

protected:
	GLuint _listId; // For generate list purpose

private:
};

