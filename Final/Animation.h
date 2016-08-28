#pragma once
#include "AnimationStep.h"

class Animation
{
public:
	Animation(msecs timeLength);
	~Animation();
	bool Execute(msecs timePassed);
	void Reset();
	Animation* AddStep(AnimationStep step);
private:
	AnimationStep* steps;
	int numberOfAnimationSteps;
	msecs timeLength;
	msecs currentTime;
};

