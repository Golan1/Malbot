#pragma once
#include "Animation.h"

// Handling all the project's animations.
// Currently only for the robot.
// Currently only 10 animations.
class AnimationManager
{
public:
	// Get the robot to work on
	AnimationManager(Robot* robot);
	~AnimationManager();

	// Choose animation to start animate
	void StartAnimate(int key);

	// Handle time interval for animations
	void Animate();

private:
	int animationToRun;
	Animation* animations[10];
};

