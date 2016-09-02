#pragma once
#include "AnimationStep.h"
class AnimationInit
{
public:
	AnimationInit(Robot* robot, AnimationType animation, GLfloat Value, Side side);
	~AnimationInit();
	void Execute();
private:
	Robot* robot;
	AnimationType animation;
	Side side;
	GLfloat value;
};

