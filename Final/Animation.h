#pragma once
#include "AnimationStep.h"
#include "AnimationInit.h"
#include "Wave.h"

// Handling animation steps and initializations
class Animation
{
public:
	Animation();

	// optional sound ctor
	Animation(char* soundFileName);
	~Animation();

	// Execute each step that needs to do something an interval of timePassed
	bool Execute(msecs timePassed);

	//Call inits and play the sound
	void Reset();

	// Add new step
	Animation* Add(AnimationStep step);

	// Add new init
	Animation* Add(AnimationInit init);

private:
	AnimationStep* steps;
	int numberOfAnimationSteps;
	msecs currentTime;

	AnimationInit* inits;
	int numberOfAnimationInits;

	Wave* sound;
};

