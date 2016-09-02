#pragma once
#include "Utils.h"

#define FOCUS_DELTA 0.5f
#define MIN_FOCUS 20.0f
#define MAX_FOCUS 40.0f

#define ATTENUATION_DELTA 0.05f
#define MAX_ATTENUATION 5.0f

#define LIGHT_SPEED 0.3f

class Light
{
public:
	Light();
	~Light();
	void Reset();
	void Activate();
	void SetDirection(GLfloat t, GLfloat p);
	void CalcMovement();
	Vector3f GetLocation();

	GLfloat SetGlobalAmbientLight(GLfloat value);

	void ControlFocus(int direction);
	void ControlAtttenuation(int direction);

	static const Vector4f WhiteColor;
private:
	void SetFocus(GLfloat f);
	void SetAttenuation(GLfloat att);

	GLfloat focus;
	GLfloat attenuation;
	GLfloat globalAmbient;

	Vector3f location, direction;
	GLfloat theta;
	GLfloat phi;

	static const Vector4f defaultLocation;
	static const Vector3f defaultDirection;
};

