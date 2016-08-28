#pragma once
#include "Robot.h"

#define msecs int
enum class AnimationType { Fist, LowerArm, UpperArm, Twist, Move };

class AnimationStep
{
public:
	AnimationStep(Robot* robot, AnimationType animation, msecs startTime, msecs endTime, GLfloat startValue, GLfloat endValue, Side side);
	~AnimationStep();
	void Execute(msecs currentTime);
private:

	Robot* robot;
	AnimationType animation;
	Side side;

	GLfloat startValue, endValue;
	msecs startTime, endTime;
};

