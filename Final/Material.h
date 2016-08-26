#pragma once
#include "Utils.h"

class Material
{
public:
	Material(Vector4f ambient, Vector4f diffues, Vector4f specular, GLdouble shininess);
	~Material();
	void Set();

private:
	Vector4f _ambient;
	Vector4f _diffuse;
	Vector4f _specular;

	GLfloat _shininess;
};

