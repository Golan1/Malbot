#include "Animation.h"


Animation::Animation(msecs timeLength) : timeLength(timeLength)
{
	numberOfAnimationSteps = 0;
	
	Reset();
}

Animation::~Animation()
{
}

bool Animation::Execute(msecs timePassed)
{
	if (currentTime < timeLength)
	{
		for (int i = 0; i < numberOfAnimationSteps; i++)
		{
			steps[i].Execute(currentTime);
		}

		currentTime += timePassed;

		return true;
	}

	return false;
}

void Animation::Reset()
{
	currentTime = 0;
}

Animation* Animation::AddStep(AnimationStep step)
{
	numberOfAnimationSteps++;
	steps = (AnimationStep*)realloc(steps, sizeof(AnimationStep) * numberOfAnimationSteps);
	steps[numberOfAnimationSteps - 1] = step;
	return this;
}
