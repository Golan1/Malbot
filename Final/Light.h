#pragma once
#include "Utils.h"

#define FOCUS_DELTA 0.5f
#define MIN_FOCUS 20.0f
#define MAX_FOCUS 40.0f

#define ATTENUATION_DELTA 0.05f
#define MAX_ATTENUATION 5.0f

#define LIGHT_SPEED 0.3f

// Handling all the light in the scene
class Light
{
public:
	Light();
	~Light();
	
	// Reset to the starting point
	void Reset();

	// Set the light into the environment
	void Activate();

	// Set spotlight direction
	void SetDirection(GLfloat t, GLfloat p);

	// Calulate if the light source needs to move
	void CalcMovement();

	// Get the light location
	Vector3f GetLocation();

	// Set global ambient
	GLfloat SetGlobalAmbientLight(GLfloat value);

	// Control light effect functions
	void ControlFocus(int direction);
	void ControlAtttenuation(int direction);

	static const Vector4f WhiteColor;
private:

	void SetFocus(GLfloat f);
	void SetAttenuation(GLfloat att);

	GLfloat focus, attenuation, globalAmbient;

	Vector3f location, direction;

	GLfloat theta, phi;

	static const Vector4f defaultLocation;
	static const Vector3f defaultDirection;
};

