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


Vector3f::Vector3f(GLdouble x, GLdouble y, GLdouble z)
{
	set(x, y, z);
}


Vector3f::Vector3f(const GLdouble *v)
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


void Vector3f::set(GLdouble x, GLdouble y, GLdouble z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}


GLdouble& Vector3f::operator[](int i)
{
	if ((i >= 0) && (i < 3))
		return vec[i];
	else if (i < 0)
		return vec[0];
	else if (i > 2)
		return vec[2];
}


GLdouble Vector3f::operator[](int i) const
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


Vector3f& Vector3f::operator*=(GLdouble s)
{
	vec[0] *= s;
	vec[1] *= s;
	vec[2] *= s;
	return *this;
}


Vector3f& Vector3f::operator/=(GLdouble s)
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


Vector3f Vector3f::operator*(GLdouble s) const
{
	return Vector3f(vec[0] * s, vec[1] * s, vec[2] * s);
}


Vector3f Vector3f::operator/(GLdouble s) const
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


GLdouble Vector3f::length(void) const
{
	return sqrt(lengthSquared());
}


GLdouble Vector3f::lengthSquared(void) const
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


GLdouble Vector3f::dot(const Vector3f& v) const
{
	return vec[0] * v.vec[0] + vec[1] * v.vec[1] + vec[2] * v.vec[2];
}


Vector3f Vector3f::cross(const Vector3f& v) const
{
	return Vector3f(vec[1] * v.vec[2] - vec[2] * v.vec[1],
		vec[2] * v.vec[0] - vec[0] * v.vec[2],
		vec[0] * v.vec[1] - vec[1] * v.vec[0]);
}


GLdouble Vector3f::distance(const Vector3f& v) const
{
	return sqrt(distanceSquared(v));
}


GLdouble Vector3f::distanceSquared(const Vector3f& v) const
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
	glVertex3d(0, 0, 0);
	glVertex3dv(vec);
	glEnd();
}