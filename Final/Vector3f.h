#pragma once
/* BASED ON: http://resumbrae.com/ub/dms424_s03/libdms/ */
/* with ideas liberally taken from OpenGL Performer's pfVec3 &
Magic Software's MgcVector3 */

#include <GL/glut.h>


class Vector3f
{
public:
	GLdouble vec[3];

	Vector3f(void);
	Vector3f(GLdouble x, GLdouble y, GLdouble z);
	Vector3f(const GLdouble *v);
	Vector3f(const Vector3f &v);
	Vector3f& operator= (const Vector3f& v);
	void set(GLdouble x, GLdouble y, GLdouble z);

	GLdouble& operator[](int i);
	GLdouble operator[](int i) const;

	Vector3f& operator+=(const Vector3f& v);
	Vector3f& operator-=(const Vector3f& v);
	Vector3f& operator*=(GLdouble s);
	Vector3f& operator/=(GLdouble s);
	Vector3f operator+(const Vector3f& v) const;
	Vector3f operator-(const Vector3f& v) const;
	Vector3f operator*(GLdouble s) const;
	Vector3f operator/(GLdouble s) const;
	Vector3f operator-(void) const;
	bool operator==(const Vector3f& v) const;
	bool operator!=(const Vector3f& v) const;

	GLdouble length(void) const;
	GLdouble lengthSquared(void) const;
	void normalize(void);
	GLdouble dot(const Vector3f& v) const;
	Vector3f cross(const Vector3f& v) const;
	GLdouble distance(const Vector3f& v) const;
	GLdouble distanceSquared(const Vector3f& v) const;

	void drawLine(void) const;

	static const Vector3f Zero;
	static const Vector3f X_Axis;
	static const Vector3f Y_Axis;
	static const Vector3f Z_Axis;

private:
};


inline Vector3f operator* (GLdouble s, const Vector3f& v) { return v*s; }