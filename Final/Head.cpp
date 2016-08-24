#include "Head.h"



Head::Head(Vector3d size) : Rect(size, false)
{
	antena = new Sphere(0.1);
}


Head::~Head()
{
	
}

void Head::Init()
{
	Rect::Init();

	antena->Init();
}

void Head::Draw()
{
	glPushMatrix();

	// rotate the head accordint to the user's view vector
	glRotatef(phi, 0, 1, 0);
	glRotatef(90 - theta, -1, 0, 0);

	glPushAttrib(GL_LINE_BIT);
	glLineWidth(2);
	glPushMatrix();
	{
		glTranslated(0, size[1], 0);
		glBegin(GL_LINES);
		glVertex3d(0, 0, 0);
		glVertex3d(0, size[1] / 2, 0);
		glEnd();

		glPopAttrib();

		glTranslated(0, size[1]/2, 0);

		antena->Draw();
	}
	glPopMatrix();
	

	Rect::Draw();
	
	glPopMatrix();
}

void Head::setDirection(GLdouble t, GLdouble p)
{
	theta = t;
	phi = p;
}
