#include "Head.h"



Head::Head(Vector3d size) : Rect(size, false)
{
}


Head::~Head()
{
}

void Head::Init()
{
	Rect::Init();
}

void Head::Draw()
{
	Rect::Draw();
}

void Head::setHeadDirection(GLdouble t, GLdouble p)
{
	theta = t;
	phi = p;
}
