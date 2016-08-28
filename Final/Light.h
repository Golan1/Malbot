#pragma once
#include "Utils.h"

#define ATTENUATION_DELTA 0.05f
#define MAX_ATTENUATION 5.0f
#define MOVE_DELTA 0.2f

class Light
{
public:
	Light(Vector4f location, Vector3f direction);
	~Light();
	void Activate();
	void SetDirection(Vector3f dir);
	void CalcMovement();

	static const Vector4f WhiteColor;
private:
	void SetAttenuation(GLfloat att);

	Vector4f location;
	Vector3f direction;
	GLfloat attenuation;
};

