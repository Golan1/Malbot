#include "Utils.h"

char Utils::keys[26];

void Utils::print(GLint x, GLint y, GLint z, char * str, void * font)
{

	glRasterPos3i(x, y, z);
	for (char *i = str; *i; i++)
	{
		glutBitmapCharacter(font, *i);
		//glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *i);
	}
}

void Utils::normalize(Vector3d vec)
{
	GLdouble normal = calcNormal(vec);
	vec[0] /= normal;
	vec[1] /= normal;
	vec[2] /= normal;
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
