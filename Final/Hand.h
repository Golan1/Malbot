#pragma once
#include "Rect.h"

#define FINGER_SPACE 0.05f
#define PHALANX_SPACE 0.06f
#define MAX_FIST_ANGLE 120.0f

class Hand :
	public Drawable
{
public:
	Hand();
	~Hand();

	void Init();
	void Draw();

	void ControlFist(int direction);
private:

	Rect* phalanx;
	Rect* palm;

	GLfloat fistAngle = 45;

	void drawPhalanxRow(bool isFirstRow = false);
};