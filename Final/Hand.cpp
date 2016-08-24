#include "Hand.h"

Hand::Hand()
{
	phalanx = new Rect({ FINGER_SPACE * 2.0, PHALANX_SPACE * 5.0, FINGER_SPACE * 2.0 });
	palm = new Rect({ 14.0 * FINGER_SPACE, PHALANX_SPACE * 15.0, FINGER_SPACE * 3.5 });
}


Hand::~Hand()
{
	delete phalanx;
	delete palm;
}


void Hand::Init()
{
	phalanx->Init();
	palm->Init();
}

void Hand::Draw()
{
	palm->Draw();

	glTranslatef((-palm->size[0] + phalanx->size[0]) / 2, palm->size[1] + PHALANX_SPACE, 0);
	glRotatef(fistAngle, 1, 0, 0);
	drawPhalanxRow();
	glTranslatef(0, phalanx->size[1] + PHALANX_SPACE, 0);
	glRotatef(fistAngle, 1, 0, 0);
	drawPhalanxRow();
	glTranslatef(0, phalanx->size[1] + PHALANX_SPACE, 0);
	glRotatef(fistAngle, 1, 0, 0);
	drawPhalanxRow(true);
}

void Hand::drawPhalanxRow(bool isFirstRow) {
	glPushMatrix();

	size_t numOfFingers;

	if (isFirstRow)
	{
		numOfFingers = 3;
		glTranslatef(phalanx->size[0] + FINGER_SPACE, 0, 0);
	}
	else
	{
		numOfFingers = 5;
	}

	for (size_t i = 0; i < numOfFingers; i++)
	{
		phalanx->Draw();

		glTranslatef(phalanx->size[0] + FINGER_SPACE, 0, 0);
	}

	glPopMatrix();
}

void Hand::ControlFist(int direction) {
	fistAngle -= direction;
	if (fistAngle < 0) fistAngle = 0;
	if (fistAngle > MAX_FIST_ANGLE) fistAngle = MAX_FIST_ANGLE;
}