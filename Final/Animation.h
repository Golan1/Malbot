#pragma once
#include "AnimationStep.h"
#include "AnimationInit.h"
#include "Wave.h"

class Animation
{
public:
	Animation();
	Animation(char* soundFileName);
	~Animation();
	bool Execute(msecs timePassed);
	void Reset();
	Animation* Add(AnimationStep step);
	Animation* Add(AnimationInit init);

private:
	AnimationStep* steps;
	int numberOfAnimationSteps;
	msecs currentTime;

	AnimationInit* inits;
	int numberOfAnimationInits;

	Wave* sound;
};

