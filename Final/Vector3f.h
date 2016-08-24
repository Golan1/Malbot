#pragma once
/* BASED ON: http://resumbrae.com/ub/dms424_s03/libdms/ */

/* with ideas liberally taken from OpenGL Performer's pfVec3 &
Magic Software's MgcVector3 */

//Use freeglut to enable multisampling
#include <GL/freeglut.h>


class Vector3f
{
public:
	GLfloat vec[3];

	Vector3f(void);
	Vector3f(GLfloat x, GLfloat y, GLfloat z);
	Vector3f(const GLfloat *v);
	Vector3f(const Vector3f &v);
	Vector3f& operator= (const Vector3f& v);
	void set(GLfloat x, GLfloat y, GLfloat z);

	GLfloat& operator[](int i);
	GLfloat operator[](int i) const;

	Vector3f& operator+=(const Vector3f& v);
	Vector3f& operator-=(const Vector3f& v);
	Vector3f& operator*=(GLfloat s);
	Vector3f& operator/=(GLfloat s);
	Vector3f operator+(const Vector3f& v) const;
	Vector3f operator-(const Vector3f& v) const;
	Vector3f operator*(GLfloat s) const;
	Vector3f operator/(GLfloat s) const;
	Vector3f operator-(void) const;
	bool operator==(const Vector3f& v) const;
	bool operator!=(const Vector3f& v) const;

	GLfloat length(void) const;
	GLfloat lengthSquared(void) const;
	void normalize(void);
	GLfloat dot(const Vector3f& v) const;
	Vector3f cross(const Vector3f& v) const;
	GLfloat distance(const Vector3f& v) const;
	GLfloat distanceSquared(const Vector3f& v) const;

	void drawLine(void) const;

	static const Vector3f Zero;
	static const Vector3f X_Axis;
	static const Vector3f Y_Axis;
	static const Vector3f Z_Axis;

private:
};


inline Vector3f operator* (GLfloat s, const Vector3f& v) { return v*s; }