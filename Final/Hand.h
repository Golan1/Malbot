#pragma once
#include "Rect.h"

#define FINGER_SPACE 0.05f
#define PHALANX_SPACE 0.06f
#define MAX_FIST_ANGLE 120.0f

// Handling the robot's hand
class Hand :
	public Drawable
{
public:
	Hand();
	~Hand();

	void Init();
	void Draw();

	// Controling fist functions
	void ControlFist(int direction);
	void SetFist(GLfloat fistAngle);

private:
	Rect* phalanx;
	Rect* palm;

	GLfloat fistAngle = 45;

	void drawPhalanxRow(bool isFirstRow = false);
};