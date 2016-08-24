#pragma once
/* BASED ON: http://resumbrae.com/ub/dms424_s03/libdms/ */
/* with ideas liberally taken from OpenGL Performer's pfVec3 &
Magic Software's MgcVector3 */

#include <GL/glut.h>


class Vector3d
{
public:
	GLdouble vec[3];

	Vector3d(void);
	Vector3d(GLdouble x, GLdouble y, GLdouble z);
	Vector3d(const GLdouble *v);
	Vector3d(const Vector3d &v);
	Vector3d& operator= (const Vector3d& v);
	void set(GLdouble x, GLdouble y, GLdouble z);

	GLdouble& operator[](int i);
	GLdouble operator[](int i) const;

	Vector3d& operator+=(const Vector3d& v);
	Vector3d& operator-=(const Vector3d& v);
	Vector3d& operator*=(GLdouble s);
	Vector3d& operator/=(GLdouble s);
	Vector3d operator+(const Vector3d& v) const;
	Vector3d operator-(const Vector3d& v) const;
	Vector3d operator*(GLdouble s) const;
	Vector3d operator/(GLdouble s) const;
	Vector3d operator-(void) const;
	bool operator==(const Vector3d& v) const;
	bool operator!=(const Vector3d& v) const;

	GLdouble length(void) const;
	GLdouble lengthSquared(void) const;
	void normalize(void);
	GLdouble dot(const Vector3d& v) const;
	Vector3d cross(const Vector3d& v) const;
	GLdouble distance(const Vector3d& v) const;
	GLdouble distanceSquared(const Vector3d& v) const;

	void drawLine(void) const;

	static const Vector3d Zero;
	static const Vector3d X_Axis;
	static const Vector3d Y_Axis;
	static const Vector3d Z_Axis;

private:
};


inline Vector3d operator* (GLdouble s, const Vector3d& v) { return v*s; }