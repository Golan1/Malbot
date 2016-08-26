#include "Material.h"



Material::Material(Vector4f ambient, Vector4f diffuse, Vector4f specular, GLdouble shininess) :
	_ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess)
{

}


Material::~Material()
{
}

void Material::Set()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient.vec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse.vec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular.vec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
}
