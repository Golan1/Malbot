#include "Sphere.h"



Sphere::Sphere(GLdouble radius) : radius(radius)
{
}


Sphere::~Sphere()
{
}

void Sphere::Init()
{
	_listId = glGenLists(1);
	glNewList(_listId, GL_COMPILE);
	glPushMatrix();

	glutSolidSphere(radius, 10, 10);

	glPopMatrix();
	glEndList();
}

void Sphere::Draw()
{
	Drawable::Draw();
}
