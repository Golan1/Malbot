#include "Head.h"



Head::Head(Vector3f size) : Rect(size, false)
{
	theta = phi = 0.0f;
	antena = new Sphere(0.025f);
}


Head::~Head()
{
	delete antena;
}

void Head::Init()
{
	Rect::Init();

	antena->Init();
}

void Head::Draw()
{
	glPushMatrix();

	// rotate the head according to the user's view vector
	glRotatef(phi, 0, 1, 0);
	glRotatef(90 - theta, -1, 0, 0);

	// Draw antena base
	glPushMatrix();
	{
		// Move to the end of the head
		glTranslated(0, size[1], 0);

		// Set line width (only for this scope)
		glPushAttrib(GL_LINE_BIT);
		glLineWidth(2);

		glBegin(GL_LINES);
		glVertex3d(0, 0, 0);
		glVertex3d(0, size[1] / 2, 0);
		glEnd();

		glPopAttrib();

		// Move to the end of the base
		glTranslated(0, size[1] / 2, 0);

		antena->Draw();
	}
	glPopMatrix();

	// Draw the head
	Rect::Draw();

	glPopMatrix();
}

void Head::SetDirection(GLfloat t, GLfloat p)
{
	theta = t;
	phi = p;
}
