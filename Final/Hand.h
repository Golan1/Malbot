#pragma once
#include "Rect.h"

#define FINGER_SPACE 0.05
#define PHALANX_SPACE 0.06
#define MAX_FIST_ANGLE 120.0

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

	GLdouble fistAngle = 45;

	void drawPhalanxRow(bool isFirstRow = false);
};