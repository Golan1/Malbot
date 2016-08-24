#include <math.h>
#include "Vector3d.h"

const Vector3d Vector3d::Zero(0.0, 0.0, 0.0);
const Vector3d Vector3d::X_Axis(1.0, 0.0, 0.0);
const Vector3d Vector3d::Y_Axis(0.0, 1.0, 0.0);
const Vector3d Vector3d::Z_Axis(0.0, 0.0, 1.0);


Vector3d::Vector3d(void)
{
	set(0, 0, 0);
}


Vector3d::Vector3d(GLdouble x, GLdouble y, GLdouble z)
{
	set(x, y, z);
}


Vector3d::Vector3d(const GLdouble *v)
{
	set(v[0], v[1], v[2]);
}


Vector3d::Vector3d(const Vector3d &v)
{
	set(v.vec[0], v.vec[1], v.vec[2]);
}


Vector3d& Vector3d::operator= (const Vector3d& v)
{
	set(v.vec[0], v.vec[1], v.vec[2]);
	return *this;
}


void Vector3d::set(GLdouble x, GLdouble y, GLdouble z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}


GLdouble& Vector3d::operator[](int i)
{
	if ((i >= 0) && (i < 3))
		return vec[i];
	else if (i < 0)
		return vec[0];
	else if (i > 2)
		return vec[2];
}


GLdouble Vector3d::operator[](int i) const
{
	if ((i >= 0) && (i < 3))
		return vec[i];
	else if (i < 0)
		return vec[0];
	else if (i > 2)
		return vec[2];
}


Vector3d& Vector3d::operator+=(const Vector3d& v)
{
	vec[0] += v.vec[0];
	vec[1] += v.vec[1];
	vec[2] += v.vec[2];
	return *this;
}


Vector3d& Vector3d::operator-=(const Vector3d& v)
{
	vec[0] -= v.vec[0];
	vec[1] -= v.vec[1];
	vec[2] -= v.vec[2];
	return *this;
}


Vector3d& Vector3d::operator*=(GLdouble s)
{
	vec[0] *= s;
	vec[1] *= s;
	vec[2] *= s;
	return *this;
}


Vector3d& Vector3d::operator/=(GLdouble s)
{
	vec[0] /= s;
	vec[1] /= s;
	vec[2] /= s;
	return *this;
}


Vector3d Vector3d::operator+(const Vector3d& v) const
{
	return Vector3d(vec[0] + v.vec[0], vec[1] + v.vec[1], vec[2] + v.vec[2]);
}


Vector3d Vector3d::operator-(const Vector3d& v) const
{
	return Vector3d(vec[0] - v.vec[0], vec[1] - v.vec[1], vec[2] - v.vec[2]);
}


Vector3d Vector3d::operator-(void) const
{
	return Vector3d(-vec[0], -vec[1], -vec[2]);
}


Vector3d Vector3d::operator*(GLdouble s) const
{
	return Vector3d(vec[0] * s, vec[1] * s, vec[2] * s);
}


Vector3d Vector3d::operator/(GLdouble s) const
{
	return Vector3d(vec[0] / s, vec[1] / s, vec[2] / s);
}


bool Vector3d::operator==(const Vector3d& v) const
{
	return ((vec[0] == v.vec[0]) &&
		(vec[1] == v.vec[1]) &&
		(vec[2] == v.vec[2]));
}


bool Vector3d::operator!=(const Vector3d& v) const
{
	return ((vec[0] != v.vec[0]) ||
		(vec[1] != v.vec[1]) ||
		(vec[2] != v.vec[2]));
}


GLdouble Vector3d::length(void) const
{
	return sqrt(lengthSquared());
}


GLdouble Vector3d::lengthSquared(void) const
{
	return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
}


void Vector3d::normalize(void)
{
	double len = length();
	if (len > 0)
	{
		vec[0] /= len;
		vec[1] /= len;
		vec[2] /= len;
	}
}


GLdouble Vector3d::dot(const Vector3d& v) const
{
	return vec[0] * v.vec[0] + vec[1] * v.vec[1] + vec[2] * v.vec[2];
}


Vector3d Vector3d::cross(const Vector3d& v) const
{
	return Vector3d(vec[1] * v.vec[2] - vec[2] * v.vec[1],
		vec[2] * v.vec[0] - vec[0] * v.vec[2],
		vec[0] * v.vec[1] - vec[1] * v.vec[0]);
}


GLdouble Vector3d::distance(const Vector3d& v) const
{
	return sqrt(distanceSquared(v));
}


GLdouble Vector3d::distanceSquared(const Vector3d& v) const
{
	double dx, dy, dz;
	dx = vec[0] - v.vec[0];
	dy = vec[1] - v.vec[1];
	dz = vec[2] - v.vec[2];
	return dx*dx + dy*dy + dz*dz;
}


void Vector3d::drawLine(void) const
{
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3dv(vec);
	glEnd();
}