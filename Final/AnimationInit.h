#pragma once
#include "AnimationStep.h"

// Handling init for specific animation
class AnimationInit
{
public:

	// choose animation type and set its value
	AnimationInit(Robot* robot, AnimationType animation, GLfloat Value, Side side);
	~AnimationInit();

	// execute the init
	void Execute();

private:
	Robot* robot;
	AnimationType animation;
	Side side;
	GLfloat value;
};

