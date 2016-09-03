#pragma once
#include "Robot.h"

#define msecs int

// All the possibles types to animate
enum class AnimationType { Fist, LowerArm, UpperArm, Twist, Move };

// Handling a single step in the animation
class AnimationStep
{
public:
	// Choose type, when to start and when to end and appropriate values to do a linear run on
	AnimationStep(Robot* robot, AnimationType animation, msecs startTime, msecs endTime, GLfloat startValue, GLfloat endValue, Side side);
	~AnimationStep();

	// Execute each interval according to the current time in the animation time
	bool Execute(msecs currentTime);
private:

	Robot* robot;
	AnimationType animation;
	Side side;

	GLfloat startValue, endValue;
	msecs startTime, endTime;
};

