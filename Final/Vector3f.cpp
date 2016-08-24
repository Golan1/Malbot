#include <math.h>
#include "Vector3f.h"

const Vector3f Vector3f::Zero(0.0, 0.0, 0.0);
const Vector3f Vector3f::X_Axis(1.0, 0.0, 0.0);
const Vector3f Vector3f::Y_Axis(0.0, 1.0, 0.0);
const Vector3f Vector3f::Z_Axis(0.0, 0.0, 1.0);


Vector3f::Vector3f(void)
{
	set(0, 0, 0);
}


Vector3f::Vector3f(GLfloat x, GLfloat y, GLfloat z)
{
	set(x, y, z);
}


Vector3f::Vector3f(const GLfloat *v)
{
	set(v[0], v[1], v[2]);
}


Vector3f::Vector3f(const Vector3f &v)
{
	set(v.vec[0], v.vec[1], v.vec[2]);
}


Vector3f& Vector3f::operator= (const Vector3f& v)
{
	set(v.vec[0], v.vec[1], v.vec[2]);
	return *this;
}


void Vector3f::set(GLfloat x, GLfloat y, GLfloat z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}


GLfloat& Vector3f::operator[](int i)
{
	if ((i >= 0) && (i < 3))
		return vec[i];
	else if (i < 0)
		return vec[0];
	else if (i > 2)
		return vec[2];
}


GLfloat Vector3f::operator[](int i) const
{
	if ((i >= 0) && (i < 3))
		return vec[i];
	else if (i < 0)
		return vec[0];
	else if (i > 2)
		return vec[2];
}


Vector3f& Vector3f::operator+=(const Vector3f& v)
{
	vec[0] += v.vec[0];
	vec[1] += v.vec[1];
	vec[2] += v.vec[2];
	return *this;
}


Vector3f& Vector3f::operator-=(const Vector3f& v)
{
	vec[0] -= v.vec[0];
	vec[1] -= v.vec[1];
	vec[2] -= v.vec[2];
	return *this;
}


Vector3f& Vector3f::operator*=(GLfloat s)
{
	vec[0] *= s;
	vec[1] *= s;
	vec[2] *= s;
	return *this;
}


Vector3f& Vector3f::operator/=(GLfloat s)
{
	vec[0] /= s;
	vec[1] /= s;
	vec[2] /= s;
	return *this;
}


Vector3f Vector3f::operator+(const Vector3f& v) const
{
	return Vector3f(vec[0] + v.vec[0], vec[1] + v.vec[1], vec[2] + v.vec[2]);
}


Vector3f Vector3f::operator-(const Vector3f& v) const
{
	return Vector3f(vec[0] - v.vec[0], vec[1] - v.vec[1], vec[2] - v.vec[2]);
}


Vector3f Vector3f::operator-(void) const
{
	return Vector3f(-vec[0], -vec[1], -vec[2]);
}


Vector3f Vector3f::operator*(GLfloat s) const
{
	return Vector3f(vec[0] * s, vec[1] * s, vec[2] * s);
}


Vector3f Vector3f::operator/(GLfloat s) const
{
	return Vector3f(vec[0] / s, vec[1] / s, vec[2] / s);
}


bool Vector3f::operator==(const Vector3f& v) const
{
	return ((vec[0] == v.vec[0]) &&
		(vec[1] == v.vec[1]) &&
		(vec[2] == v.vec[2]));
}


bool Vector3f::operator!=(const Vector3f& v) const
{
	return ((vec[0] != v.vec[0]) ||
		(vec[1] != v.vec[1]) ||
		(vec[2] != v.vec[2]));
}


GLfloat Vector3f::length(void) const
{
	return sqrt(lengthSquared());
}


GLfloat Vector3f::lengthSquared(void) const
{
	return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
}


void Vector3f::normalize(void)
{
	double len = length();
	if (len > 0)
	{
		vec[0] /= len;
		vec[1] /= len;
		vec[2] /= len;
	}
}


GLfloat Vector3f::dot(const Vector3f& v) const
{
	return vec[0] * v.vec[0] + vec[1] * v.vec[1] + vec[2] * v.vec[2];
}


Vector3f Vector3f::cross(const Vector3f& v) const
{
	return Vector3f(vec[1] * v.vec[2] - vec[2] * v.vec[1],
		vec[2] * v.vec[0] - vec[0] * v.vec[2],
		vec[0] * v.vec[1] - vec[1] * v.vec[0]);
}


GLfloat Vector3f::distance(const Vector3f& v) const
{
	return sqrt(distanceSquared(v));
}


GLfloat Vector3f::distanceSquared(const Vector3f& v) const
{
	double dx, dy, dz;
	dx = vec[0] - v.vec[0];
	dy = vec[1] - v.vec[1];
	dz = vec[2] - v.vec[2];
	return dx*dx + dy*dy + dz*dz;
}


void Vector3f::drawLine(void) const
{
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3fv(vec);
	glEnd();
}