#include "Floor.h"

Floor::Floor(GLint size)
{
	_size = size;
	_texture = new Texture2D("Textures\\parquet.jpg");

	Vector4f base = { 1.0f, 1.0f, 1.0f, 1.0f };

	_material = new Material(base * 0.2, base, base, 10.f);
}


Floor::~Floor()
{
	delete _texture;
}

void Floor::Init()
{
	_texture->Init();

	_listId = glGenLists(1);
	glNewList(_listId, GL_COMPILE);

	_material->Set();

	_texture->Enable();

	int j, i;

	glBegin(GL_QUADS);

	glNormal3fv(Vector3f::Y_Axis.vec);

	GLint limit = -_size / 2;
	int step = 1;

	for (i = 0; i < _size; i += step)
		for (j = 1; j <= _size; j += step)
		{
			glTexCoord2d(0, 0);
			glVertex3d(limit + i, 0.0, limit + j);
			glTexCoord2d(1, 0);
			glVertex3d(limit + i, 0.0, limit + j - step);
			glTexCoord2d(1, 1);
			glVertex3d(limit + i + step, 0.0, limit + j - step);
			glTexCoord2d(0, 1);
			glVertex3d(limit + i + step, 0.0, limit + j);
		}
	glEnd();

	_texture->Disable();

	glEndList();
}

//
//void Floor::Init()
//{
//	_listId = glGenLists(1);
//	glNewList(_listId, GL_COMPILE);
//
//	_material->Set();
//
//
//	glBegin(GL_QUADS);
//
//	glNormal3fv(Vector3f::Y_Axis.vec);
//
//	GLint limit = -_size / 2;
//
//	glVertex3d(limit, 0.0, limit);
//	glVertex3d(limit, 0.0, -limit);
//	glVertex3d(-limit, 0.0, -limit);
//	glVertex3d(-limit, 0.0, limit);
//	glEnd();
//
//	glEndList();
//}