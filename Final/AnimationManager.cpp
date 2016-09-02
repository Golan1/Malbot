#include "AnimationManager.h"

AnimationManager::AnimationManager(Robot* robot)
{
	animationToRun = -1;

	// Freeze
	animations[0] = (new Animation("Sounds\\freeze.wav"))
		->Add(AnimationInit(robot, AnimationType::Fist, 0.0f, Side::Both))
		->Add(AnimationInit(robot, AnimationType::LowerArm, 0.0f, Side::Both))
		->Add(AnimationInit(robot, AnimationType::UpperArm, 0.0f, Side::Both));

	// Bye Bye
	animations[1] = (new Animation("Sounds\\ill-be-back.wav"))
		->Add(AnimationInit(robot, AnimationType::UpperArm, 90.0f, Side::Left))
		->Add(AnimationInit(robot, AnimationType::LowerArm, 90.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Fist, 0, 500, 0.0f, 20.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Fist, 500, 1000, 20.0f, 0.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Fist, 1000, 1500, 0.0f, 20.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Fist, 1500, 2000, 20.0f, 0.0f, Side::Left));

	// Pray
	animations[2] = (new Animation("Sounds\\pray.wav"))
		->Add(AnimationInit(robot, AnimationType::Fist, 0.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 700, 90.0f, 0.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 700, 45.0f, 90.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 700, 1400, 0.0f, 90.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 700, 1400, 90.0f, 45.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 1400, 2100, 90.0f, 0.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1400, 2100, 45.0f, 90.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 2100, 2800, 0.0f, 90.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 2100, 2800, 90.0f, 45.0f, Side::Both));

	// Victory
	animations[3] = (new Animation("Sounds\\yes-hahahaa.wav"))
		->Add(AnimationInit(robot, AnimationType::Fist, MAX_FIST_ANGLE, Side::Both))
		->Add(AnimationInit(robot, AnimationType::LowerArm, MAX_ELBOW_ANGLE, Side::Left))
		->Add(AnimationInit(robot, AnimationType::UpperArm, 180.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 300, MAX_ELBOW_ANGLE / 2, 0.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 300, 130.0f, 30.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::Twist, 0, 1500, 5.0f, 15.0f, Side::Right));

	// Swim
	animations[4] = (new Animation("Sounds\\swim.wav"))
		->Add(AnimationInit(robot, AnimationType::Fist, 40.0f, Side::Both))
		->Add(AnimationInit(robot, AnimationType::LowerArm, 0.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 3000, -270.0f, 450.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 3000, -90.0f, 630.0f, Side::Left));

	// Pull
	animations[5] = (new Animation())
		->Add(AnimationStep(robot, AnimationType::Fist, 0, 500, 0.0f, MAX_FIST_ANGLE, Side::Both))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 500, 0.0f, MAX_ELBOW_ANGLE, Side::Both))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 500, 90.0f, 180.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::Move, 0, 500, 0.0f, 0.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::Fist, 500, 1000, MAX_FIST_ANGLE, 0.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 500, 1000, MAX_ELBOW_ANGLE, 0.0f, Side::Both))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 500, 1000, 180.0f, 90.0f, Side::Both));

	// Run
	animations[6] = (new Animation("Sounds\\fg-run.wav"))
		->Add(AnimationInit(robot, AnimationType::Fist, MAX_FIST_ANGLE, Side::Both))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 500, MAX_ELBOW_ANGLE, 50.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 500, 180.0f, 90.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 500, 1000, 50.0f, MAX_ELBOW_ANGLE, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 500, 1000, 90.0f, 180.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 1000, 1500, MAX_ELBOW_ANGLE, 50.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1000, 1500, 180.0f, 90.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 1500, 2000, 50.0f, MAX_ELBOW_ANGLE, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1500, 2000, 90.0f, 180.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 500, 50.0f, MAX_ELBOW_ANGLE, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 500, 90.0f, 180.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 500, 1000, MAX_ELBOW_ANGLE, 50.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 500, 1000, 180.0f, 90.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 1000, 1500, 50.0f, MAX_ELBOW_ANGLE, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1000, 1500, 90.0f, 180.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 1500, 2000, MAX_ELBOW_ANGLE, 50.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1500, 2000, 180.0f, 90.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Move, 0, 2000, 0.0f, 0.0f, Side::Both));

	// Helicopter
	animations[7] = (new Animation("Sounds\\helicopter.wav"))
		->Add(AnimationInit(robot, AnimationType::Fist, 0.0f, Side::Both))
		->Add(AnimationInit(robot, AnimationType::LowerArm, 0.0f, Side::Both))
		->Add(AnimationInit(robot, AnimationType::UpperArm, 90.0f, Side::Left))
		->Add(AnimationInit(robot, AnimationType::UpperArm, 270.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::Twist, 0, 3300, 0.0f, 30.0f, Side::Left));

	// Thriller
	animations[8] = (new Animation("Sounds\\thriller.wav"))
		->Add(AnimationInit(robot, AnimationType::Fist, 45.0f, Side::Both))

		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 300, 100.0f, 60.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 300, 130.0f, 60.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 300, 60.0f, 100.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 300, 60.0f, 130.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Twist, 0, 300, 5.0f, 5.0f, Side::Left))

		->Add(AnimationStep(robot, AnimationType::LowerArm, 500, 800, 100.0f, 60.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 500, 800, 130.0f, 60.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 500, 800, 60.0f, 100.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 500, 800, 60.0f, 130.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::Twist, 500, 800, 10.0f, 10.0f, Side::Right))

		->Add(AnimationStep(robot, AnimationType::LowerArm, 1000, 1300, 100.0f, 60.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1000, 1300, 130.0f, 60.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 1000, 1300, 60.0f, 100.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1000, 1300, 60.0f, 130.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Twist, 1000, 1300, 10.0f, 10.0f, Side::Left))

		->Add(AnimationStep(robot, AnimationType::Move, 1500, 1700, 1.0f, 1.0f, Side::Both))

		->Add(AnimationStep(robot, AnimationType::LowerArm, 1700, 2000, 100.0f, 60.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1700, 2000, 130.0f, 60.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 1700, 2000, 60.0f, 100.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 1700, 2000, 60.0f, 130.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::Twist, 1700, 2000, 10.0f, 10.0f, Side::Right))

		->Add(AnimationStep(robot, AnimationType::LowerArm, 2200, 2500, 100.0f, 60.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 2200, 2500, 130.0f, 60.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 2200, 2500, 60.0f, 100.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 2200, 2500, 60.0f, 130.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::Twist, 2200, 2500, 10.0f, 10.0f, Side::Left))

		->Add(AnimationStep(robot, AnimationType::LowerArm, 2700, 3000, 100.0f, 60.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 2700, 3000, 130.0f, 60.0f, Side::Left))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 2700, 3000, 60.0f, 100.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 2700, 3000, 60.0f, 130.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::Twist, 2700, 3000, 10.0f, 10.0f, Side::Right))

		->Add(AnimationStep(robot, AnimationType::Twist, 3200, 3800, 15.0f, 15.0f, Side::Left))
		;

	animations[9] = (new Animation("Sounds\\hand.wav"))
		->Add(AnimationStep(robot, AnimationType::Fist, 0, 700, MAX_FIST_ANGLE, 0.0, Side::Right))
		->Add(AnimationStep(robot, AnimationType::LowerArm, 0, 700, 30.0f, 90.0f, Side::Right))
		->Add(AnimationStep(robot, AnimationType::UpperArm, 0, 700, 180.0f, 90.0f, Side::Right))
		;
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
	if (animationToRun != -1 && animations[animationToRun] != NULL) {
		if (animations[animationToRun]->Execute(1000 / FPS)) animationToRun = -1;
	}
}
