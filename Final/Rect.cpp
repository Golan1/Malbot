#include "Rect.h"



Rect::Rect(Vector3f size, bool isSolid) : size(size), _isSolid(isSolid)
{
}



Rect::~Rect()
{
}	

void Rect::Init() {
	_listId = glGenLists(1);
	glNewList(_listId, GL_COMPILE);
	glPushMatrix();

	Utils::glScalefv(size); // scale to the correct size

	glTranslatef(0, 0.5, 0); // start from the base of the cube

	_isSolid ? glutSolidCube(1.0) : glutWireCube(1.0);

	glPopMatrix();
	glEndList();
}

void Rect::Draw()
{
	Drawable::Draw();
}
