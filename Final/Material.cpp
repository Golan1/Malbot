#include "Material.h"

// Default materials
const Material Material::Brass({ 0.329412f,0.223529f, 0.027451f, 1.0f }, { 0.780392f, 0.568627f, 0.113725f , 1.0f }, { 0.992157f, 0.941176f, 0.807843f , 1.0f }, 0.21794872 * 128.0f);
const Material Material::Chrome({ 0.25f, 0.25f, 0.25f , 1.0f }, { 0.4f, 0.4f, 0.4f , 1.0f }, { 0.774597f,  0.774597f, 0.774597f , 1.0f }, 0.6f * 128.0f);
const Material Material::Gold({ 0.24725f, 0.1995f, 0.0745f, 1.0f }, { 0.75164f, 0.60648f, 0.22648f, 1.0f }, { 0.628281f, 0.555802f, 0.366065f, 1.0f }, 0.4f * 128.0f);
const Material Material::RedRubber({ 0.05f, 0.0f, 0.0f,1.0f }, { 0.5f, 0.4f, 0.4f, 1.0f }, { 0.7f, 0.04f, 0.04f, 1.0f }, 0.078125f * 128.0f);
const Material Material::Emerald({ 0.0215f, 0.1745f, 0.0215f, 1.0f }, { 0.07568f, 0.61424f, 0.07568f, 1.0f }, { 0.633f, 0.727811f, 0.633f, 1.0f }, 0.6f * 128.0f);

Material::Material(Vector4f ambient, Vector4f diffuse, Vector4f specular, GLfloat shininess) :
	_ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess)
{

}

Material::Material(Vector4f baseColor, GLfloat ambientFactor, GLfloat diffuseFactor, GLfloat specularFactor, GLfloat shininess) :
	Material(baseColor * ambientFactor, baseColor * diffuseFactor, baseColor * specularFactor, shininess)
{

}

Material::~Material()
{
}

void Material::Set() const
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient.vec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse.vec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular.vec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);
}