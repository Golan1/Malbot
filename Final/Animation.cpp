#include "Animation.h"


Animation::Animation()
{
	numberOfAnimationSteps = 0;
	numberOfAnimationInits = 0;
}

Animation::Animation(char * soundFileName) :Animation()
{
	sound = new Wave(soundFileName);
}

Animation::~Animation()
{
}

bool Animation::Execute(msecs timePassed)
{
	bool finished = true;

	for (int i = 0; i < numberOfAnimationSteps; i++)
	{
		finished = steps[i].Execute(currentTime) && finished;
	}

	currentTime += timePassed;

	return finished;
}

void Animation::Reset()
{
	currentTime = 0;

	for (int i = 0; i < numberOfAnimationInits; i++)
	{
		inits[i].Execute();
	}

	if (sound != NULL) {
		sound->play();
	}
}

Animation* Animation::Add(AnimationStep step)
{
	numberOfAnimationSteps++;
	steps = (AnimationStep*)realloc(steps, sizeof(AnimationStep) * numberOfAnimationSteps);
	steps[numberOfAnimationSteps - 1] = step;
	return this;
}

Animation* Animation::Add(AnimationInit init)
{
	numberOfAnimationInits++;
	inits = (AnimationInit*)realloc(inits, sizeof(AnimationInit) * numberOfAnimationInits);
	inits[numberOfAnimationInits - 1] = init;
	return this;
}
