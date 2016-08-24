#pragma once
#include "GL\glut.h"
#include "Vector3f.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

class Utils
{
public:
	static char keys[26];

	inline static double degToRad(double x) { return x * PI / 180; };
	inline static void glScalefv(Vector3f vec) { glScalef(vec[0], vec[1], vec[2]); }
	static void print(GLint x, GLint y, GLint z, char *str, void *font);

	static bool isKeyPressed(char key);
	
private:
	Utils() {};
};

