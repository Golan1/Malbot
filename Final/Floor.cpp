#include "Floor.h"
#include "Light.h"

Floor::Floor(GLint size)
{
	_size = size;
	_texture = new Texture2D("Textures\\parquet.jpg");

	_material = new Material(Light::WhiteColor, 0.2f, 1.0f, 0.7f, 50.0f);
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

	for (i = 0; i < _size; i += 1)
	{
		for (j = 1; j <= _size; j += 1)
		{
			glTexCoord2d(0.0f, 0.0f);
			glVertex3f(limit + i, 0.0f, limit + j);
			glTexCoord2f(1, 0);
			glVertex3f(limit + i, 0.0f, limit + j - 1);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(limit + i + 1, 0.0f, limit + j - 1);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(limit + i + 1, 0.0f, limit + j);
		}
	}
	glEnd();

	_texture->Disable();

	glEndList();
}