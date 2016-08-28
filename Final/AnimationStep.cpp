#include "AnimationStep.h"

AnimationStep::AnimationStep(Robot* robot, AnimationType animation, msecs startTime, msecs endTime, GLfloat startValue, GLfloat endValue, Side side = Side::Both) :
	robot(robot), animation(animation),startTime(startTime), endTime(endTime), startValue(startValue), endValue(endValue), side(side)
{
}


AnimationStep::~AnimationStep()
{

}

void AnimationStep::Execute(msecs currentTime) {

	if (currentTime < startTime || currentTime > endTime) return;

	GLfloat length = endTime - startTime;

	GLfloat currentValue = startValue + (currentTime - startTime) / length * (endValue - startValue);

	switch (animation)
	{
	case AnimationType::Fist:
	{
		robot->SetFist(currentValue, side);
		break;
	}
	case AnimationType::LowerArm:
		robot->SetLowerArm(currentValue, side);
		break;
	case AnimationType::UpperArm:
		robot->SetUpperArm(currentValue, side);
		break;
	case AnimationType::Twist:
		break;
	case AnimationType::Move:
		robot->MoveForward();
		break;
	default:
		break;
	}
}