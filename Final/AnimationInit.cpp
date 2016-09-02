#include "AnimationInit.h"


AnimationInit::AnimationInit(Robot * robot, AnimationType animation, GLfloat value, Side side) :
	robot(robot), animation(animation), value(value), side(side)
{
}

AnimationInit::~AnimationInit()
{
}

void AnimationInit::Execute()
{
	switch (animation)
	{
	case AnimationType::Fist:
	{
		robot->SetFist(value, side);
		break;
	}
	case AnimationType::LowerArm:
		robot->SetLowerArm(value, side);
		break;
	case AnimationType::UpperArm:
		robot->SetUpperArm(value, side);
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