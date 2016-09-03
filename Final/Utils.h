#pragma once
#include "Vector3f.h"
#include "Vector4f.h"
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

#define FPS 60

enum  class Side { Both, Right, Left };

// General utils
class Utils
{
public:
	static bool keys[26];

	inline static GLfloat degToRad(GLfloat x) { return x * PI / 180; };
	inline static void glScalefv(Vector3f vec) { glScalef(vec[0], vec[1], vec[2]); }
	inline static void glTranslatefv(Vector3f vec) { glTranslatef(vec[0], vec[1], vec[2]); }
	static void print(GLint x, GLint y, GLint z, char *str, void *font);
	static bool isKeyPressed(char key);
	static Vector3f getDirectionVector(GLfloat theta, GLfloat phi);
	
private:
	Utils() {};
};

