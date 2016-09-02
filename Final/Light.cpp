#include "Light.h"

const Vector4f Light::WhiteColor(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4f Light::defaultLocation(0.0f, 0.0f, 0.0f, 1.0f);
const Vector3f Light::defaultDirection(0.0f, 0.0f, -1.0f);

Light::Light()
{
	globalAmbient = 1.0f;
}

Light::~Light()
{
}

void Light::Reset() {
	focus = MAX_FOCUS;
	attenuation = 0.5f;
	theta = 120.0f;
	phi = 0.0f;
	location = { 0.0f, 10.0f, 0.0f };
}

void Light::Activate()
{
	glPushMatrix();

	Utils::glTranslatefv(location.vec);

	// rotate the cone according to the user's defined vector
	glRotatef(phi, 0, 1, 0);
	glRotatef(90 + theta, 1, 0, 0);

	glutWireCone(0.5f + focus / MAX_FOCUS * 0.5, 1.0f, 10, 10);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, defaultDirection.vec);
	glLightfv(GL_LIGHT0, GL_POSITION, defaultLocation.vec);
	glPopMatrix();

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (Light::WhiteColor * globalAmbient).vec);

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light::WhiteColor.vec);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light::WhiteColor.vec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light::WhiteColor.vec);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuation);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, focus);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 6.0f);

	glEnable(GL_LIGHT0);
}

void Light::SetDirection(GLfloat t, GLfloat p)
{
	theta = t;
	phi = p;
	direction = Utils::getDirectionVector(theta, phi);
}

void Light::CalcMovement()
{
	int moveDirection = 0;

	if (Utils::isKeyPressed('w')) {
		moveDirection = 1;
	}
	else if (Utils::isKeyPressed('s')) {
		moveDirection = -1;
	}
	location += moveDirection * direction * LIGHT_SPEED;

	if (location[1] < 0.1f) location[1] = 0.1f;
}
//
//void Light::CalcAttenuation() {
//	if (Utils::isKeyPressed('y')) {
//		SetAttenuation(attenuation - ATTENUATION_DELTA);
//	}
//	else if (Utils::isKeyPressed('h')) {
//		SetAttenuation(attenuation + ATTENUATION_DELTA);
//	}
//
//	if (Utils::isKeyPressed('u')) {
//		SetFocus(focus - FOCUS_DELTA);
//	}
//	else if (Utils::isKeyPressed('j')) {
//		SetFocus(focus + FOCUS_DELTA);
//	}
//}

void Light::ControlFocus(int direction) {
	SetFocus(focus - FOCUS_DELTA * direction);
}

void Light::SetFocus(GLfloat f) {
	if (f < MIN_FOCUS) focus = MIN_FOCUS;
	else if (f> MAX_FOCUS) focus = MAX_FOCUS;
	else focus = f;
}

void Light::ControlAtttenuation(int direction) {
	SetAttenuation(attenuation - ATTENUATION_DELTA * direction);
}

void Light::SetAttenuation(GLfloat att)
{
	if (att > MAX_ATTENUATION) attenuation = MAX_ATTENUATION;
	else if (att < 0) attenuation = 0;
	else attenuation = att;
}

Vector3f Light::GetLocation() {
	return location;
}

GLfloat Light::SetGlobalAmbientLight(GLfloat value)
{
	if (value < 0.0f) globalAmbient = value;
	else if (value > 1.0f) globalAmbient = 1.0f;
	else globalAmbient = value;

	return globalAmbient;
}