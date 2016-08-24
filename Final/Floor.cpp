#include "Floor.h"



Floor::Floor(int size)
{
	_size = size;
	_texture = new Texture2D("Textures\\parquet.jpg");
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

	_texture->Enable();

	int j, i;

	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);

	GLfloat limit = -_size / 2;

	for (i = 0; i < _size; i++)
		for (j = 1; j <= _size; j++)
		{
			glTexCoord2d(0, 0);
			glVertex3d(limit + i, 0.0, limit + j);
			glTexCoord2d(1, 0);
			glVertex3d(limit + i + 1, 0.0, limit + j);
			glTexCoord2d(1, 1);
			glVertex3d(limit + i + 1, 0.0, limit + j - 1);
			glTexCoord2d(0, 1);
			glVertex3d(limit + i, 0.0, limit + j - 1);
		}

	_texture->Disable();
	glEnd();

	glEndList();
}
