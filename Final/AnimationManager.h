#pragma once
#include "Animation.h"

class AnimationManager
{
public:
	AnimationManager(Robot* robot);
	~AnimationManager();
	void StartAnimate(int key);
	void Animate();
private:
	int animationToRun;
	Animation* animations[10];
};

