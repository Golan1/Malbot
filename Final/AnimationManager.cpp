#include "AnimationManager.h"



AnimationManager::AnimationManager(Robot* robot)
{
	animationToRun = -1;

	animations[0] = new Animation(2000);
	animations[0]
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 0, 20, -90.0f, -90.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 0, 20, 90.0f, 90.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::Fist, 0, 500, 0.0f, 20.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::Fist, 500, 1000, 20.0f, 0.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::Fist, 1000, 1500, 0.0f, 20.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::Fist, 1500, 2000, 20.0f, 0.0f, Side::Left));

	animations[1] = new Animation(2000);
	animations[1]
		->AddStep(AnimationStep(robot, AnimationType::Fist, 0, 20, 0.0f, 0.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 0, 500, 90.0f, 0.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 500, 1000, 0.0f, 90.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 1000, 1500, 90.0f, 0.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 1500, 2000, 0.0f, 90.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 0, 500, -45.0f, -90.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 500, 1000, -90.0f, -45.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 1000, 1500, -45.0f, -90.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 1500, 2000, -90.0f, -45.0f, Side::Both));

	animations[2] = new Animation(2000);
	animations[2]
		->AddStep(AnimationStep(robot, AnimationType::Fist, 0, 20, MAX_FIST_ANGLE, MAX_FIST_ANGLE, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 0, 500, MAX_ELBOW_ANGLE, 0.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 0, 500, 0.0f, MAX_ELBOW_ANGLE, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 0, 500, 0.0f, 180.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 0, 500, 0.0f, 180.0f, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 500, 1000, 0.0f, MAX_ELBOW_ANGLE, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 500, 1000, MAX_ELBOW_ANGLE, 0.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 500, 1000, 0.0f, 180.0f, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 500, 1000, 0.0f, 180.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 1000, 1500, MAX_ELBOW_ANGLE, 0.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 1000, 1500, 0.0f, MAX_ELBOW_ANGLE, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 1000, 1500, 0.0f, 180.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 1000, 1500, 0.0f, 180.0f, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 1500, 2000, 0.0f, MAX_ELBOW_ANGLE, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 1500, 2000, MAX_ELBOW_ANGLE, 0.0f, Side::Left))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 1500, 2000, 0.0f, 180.0f, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 1500, 2000, 0.0f, 180.0f, Side::Left));

	animations[3] = new Animation(5000);
	animations[3]
		->AddStep(AnimationStep(robot, AnimationType::Fist, 0, 20, 40.0f, 40.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 0, 20, 0.0f, 0.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 0, 3000, 270.0f, -450.0f, Side::Right))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 0, 3000, 90.0f, -630.0f, Side::Left));

	animations[4] = new Animation(5000);
	animations[4]
		->AddStep(AnimationStep(robot, AnimationType::Fist, 0, 500, 0.0f, MAX_FIST_ANGLE, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 0, 500, 0.0f, MAX_ELBOW_ANGLE, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 0, 500, -90.0f, -180.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::Move, 0, 500, 0.0f, 0.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::Fist, 500, 1000, MAX_FIST_ANGLE, 0.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::LowerArm, 500, 1000, MAX_ELBOW_ANGLE, 0.0f, Side::Both))
		->AddStep(AnimationStep(robot, AnimationType::UpperArm, 500, 1000, -180.0f, -90.0f, Side::Both));

	animations[5] = new Animation(5000);
	animations[6] = new Animation(5000);
	animations[7] = new Animation(5000);
	animations[8] = new Animation(5000);
	animations[9] = new Animation(5000);
}


AnimationManager::~AnimationManager()
{
}

void AnimationManager::StartAnimate(int key)
{
	animationToRun = key;

	animations[animationToRun]->Reset();
}

void AnimationManager::Animate()
{
	if (animationToRun != -1) {
		if (!animations[animationToRun]->Execute(1000 / FPS)) animationToRun = -1;
	}
}
