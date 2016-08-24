#pragma once
/* BASED ON: http://resumbrae.com/ub/dms424_s03/libdms/ */

/* with ideas liberally taken from OpenGL Performer's pfVec3 &
Magic Software's MgcVector4f */

//Use freeglut to enable multisampling
#include <GL/freeglut.h>

class Vector4f
{
public:
	GLfloat vec[4];

	Vector4f(void);
	Vector4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	Vector4f(const GLfloat *v);
	Vector4f(const Vector4f &v);
	Vector4f& operator= (const Vector4f& v);
	void set(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

	GLfloat& operator[](int i);
	GLfloat operator[](int i) const;

	Vector4f& operator+=(const Vector4f& v);
	Vector4f& operator-=(const Vector4f& v);
	Vector4f& operator*=(GLfloat s);
	Vector4f& operator/=(GLfloat s);
	Vector4f operator+(const Vector4f& v) const;
	Vector4f operator-(const Vector4f& v) const;
	Vector4f operator*(GLfloat s) const;
	Vector4f operator/(GLfloat s) const;
	Vector4f operator-(void) const;
	bool operator==(const Vector4f& v) const;
	bool operator!=(const Vector4f& v) const;

	GLfloat length(void) const;
	GLfloat lengthSquared(void) const;
	void normalize(void);
	GLfloat dot(const Vector4f& v) const;
	GLfloat distance(const Vector4f& v) const;
	GLfloat distanceSquared(const Vector4f& v) const;

	static const Vector4f Zero;
private:
};