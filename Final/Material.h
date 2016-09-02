#pragma once
#include "Utils.h"

class Material
{
public:
	Material(Vector4f ambient, Vector4f diffues, Vector4f specular, GLfloat shininess);
	Material(Vector4f baseColor, GLfloat ambientFactor, GLfloat diffuseFactor, GLfloat specularFactor, GLfloat shininess);
	~Material();
	void Set() const;

	static const Material Brass;
	static const Material Chrome;
	static const Material Gold;
	static const Material RedRubber;
	static const Material Emerald;

private:
	Vector4f _ambient;
	Vector4f _diffuse;
	Vector4f _specular;

	GLfloat _shininess;
};

