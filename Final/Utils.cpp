#include "Utils.h"
#include <stdio.h>

bool Utils::keys[26];

void Utils::print(GLint x, GLint y, GLint z, char * str, void * font)
{

	glRasterPos3i(x, y, z);
	for (char *i = str; *i; i++)
	{
		glutBitmapCharacter(font, *i);
	}
}

bool Utils::isKeyPressed(char key)
{
	if (key >= 65 && key <= 90) {
		return keys[key - 65];
	}
	else if (key >= 97 && key <= 122) {
		return keys[key - 97];
	}

	return false;
}

// Get spherical direction according to the angles
Vector3f Utils::getDirectionVector(GLfloat theta, GLfloat phi)
{
	GLfloat p = Utils::degToRad(phi);
	GLfloat t = Utils::degToRad(theta);

	Vector3f direction = { sinf(p) * sinf(t), cosf(t), cosf(p) * sinf(t) };

	direction.normalize();

	return direction;
}
