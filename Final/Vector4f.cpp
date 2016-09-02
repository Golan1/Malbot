#include "Vector4f.h"

#include <math.h>

const Vector4f Vector4f::Zero(0.0, 0.0, 0.0, 0.0);

Vector4f::Vector4f(void)
{
	set(0, 0, 0, 0);
}


Vector4f::Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	set(x, y, z, w);
}


Vector4f::Vector4f(const GLfloat *v)
{
	set(v[0], v[1], v[2], v[3]);
}


Vector4f::Vector4f(const Vector4f &v)
{
	set(v.vec[0], v.vec[1], v.vec[2], v.vec[3]);
}


Vector4f& Vector4f::operator= (const Vector4f& v)
{
	set(v.vec[0], v.vec[1], v.vec[2], v.vec[3]);
	return *this;
}


void Vector4f::set(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
	vec[3] = w;
}


GLfloat& Vector4f::operator[](int i)
{
	if ((i >= 0) && (i < 4))
		return vec[i];
	else if (i < 0)
		return vec[0];
	else if (i > 3)
		return vec[3];
}


GLfloat Vector4f::operator[](int i) const
{
	if ((i >= 0) && (i < 4))
		return vec[i];
	else if (i < 0)
		return vec[0];
	else if (i > 3)
		return vec[3];
}


Vector4f& Vector4f::operator+=(const Vector4f& v)
{
	vec[0] += v.vec[0];
	vec[1] += v.vec[1];
	vec[2] += v.vec[2];
	vec[3] += v.vec[3];
	return *this;
}


Vector4f& Vector4f::operator-=(const Vector4f& v)
{
	vec[0] -= v.vec[0];
	vec[1] -= v.vec[1];
	vec[2] -= v.vec[2];
	vec[3] -= v.vec[3];
	return *this;
}


Vector4f& Vector4f::operator*=(GLfloat s)
{
	vec[0] *= s;
	vec[1] *= s;
	vec[2] *= s;
	//vec[3] *= s;
	return *this;
}


Vector4f& Vector4f::operator/=(GLfloat s)
{
	vec[0] /= s;
	vec[1] /= s;
	vec[2] /= s;
	//vec[3] /= s;
	return *this;
}


Vector4f Vector4f::operator+(const Vector4f& v) const
{
	return Vector4f(vec[0] + v.vec[0], vec[1] + v.vec[1],
		vec[2] + v.vec[2], vec[3] + v.vec[3]);
}


Vector4f Vector4f::operator-(const Vector4f& v) const
{
	return Vector4f(vec[0] - v.vec[0], vec[1] - v.vec[1],
		vec[2] - v.vec[2], vec[3] - v.vec[3]);
}


Vector4f Vector4f::operator*(GLfloat s) const
{
	//return Vector4f(vec[0] * s, vec[1] * s, vec[2] * s, vec[3] * s);
	return Vector4f(vec[0] * s, vec[1] * s, vec[2] * s, vec[3]);
}


Vector4f Vector4f::operator/(GLfloat s) const
{
	//return Vector4f(vec[0] / s, vec[1] / s, vec[2] / s, vec[3] / s);
	return Vector4f(vec[0] / s, vec[1] / s, vec[2] / s, vec[3]);
}


Vector4f Vector4f::operator-(void) const
{
	return Vector4f(-vec[0], -vec[1], -vec[2], -vec[3]);
}


bool Vector4f::operator==(const Vector4f& v) const
{
	return ((vec[0] == v.vec[0]) &&
		(vec[1] == v.vec[1]) &&
		(vec[2] == v.vec[2]) &&
		(vec[3] == v.vec[3]));
}


bool Vector4f::operator!=(const Vector4f& v) const
{
	return ((vec[0] != v.vec[0]) ||
		(vec[1] != v.vec[1]) ||
		(vec[2] != v.vec[2]) ||
		(vec[3] != v.vec[3]));
}


GLfloat Vector4f::length(void) const
{
	return sqrt(lengthSquared());
}


GLfloat Vector4f::lengthSquared(void) const
{
	return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] + vec[3] * vec[3];
}


void Vector4f::normalize(void)
{
	float len = length();
	if (len > 0)
	{
		vec[0] /= len;
		vec[1] /= len;
		vec[2] /= len;
		vec[3] /= len;
	}
}


GLfloat Vector4f::dot(const Vector4f& v) const
{
	return vec[0] * v.vec[0] + vec[1] * v.vec[1] + vec[2] * v.vec[2]
		+ vec[3] * v.vec[3];
}


GLfloat Vector4f::distance(const Vector4f& v) const
{
	return sqrt(distanceSquared(v));
}


GLfloat Vector4f::distanceSquared(const Vector4f& v) const
{
	float dx, dy, dz, dw;
	dx = vec[0] - v.vec[0];
	dy = vec[1] - v.vec[1];
	dz = vec[2] - v.vec[2];
	dw = vec[3] - v.vec[3];
	return dx*dx + dy*dy + dz*dz + dw*dw;
}