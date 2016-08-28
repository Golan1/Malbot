#include "Light.h"

const Vector4f Light::WhiteColor(1.0f, 1.0f, 1.0f, 1.0f);

Light::Light(Vector4f location, Vector3f direction) : location(location), direction(direction)
{
	attenuation = 0.0f;
}


Light::~Light()
{
}

void Light::Activate()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light::WhiteColor.vec);

	glLightfv(GL_LIGHT0, GL_POSITION, location.vec);

	glLightfv(GL_LIGHT0, GL_AMBIENT, Light::WhiteColor.vec);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light::WhiteColor.vec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Light::WhiteColor.vec);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuation);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction.vec);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 6.0f);

	glEnable(GL_LIGHT0);
}

void Light::SetDirection(Vector3f dir)
{
	if (Utils::isKeyPressed('p')) {
		direction = dir;
	}
}

void Light::CalcMovement()
{
	if (Utils::isKeyPressed('i')) {
		location[0] += MOVE_DELTA;
	}
	else if (Utils::isKeyPressed('k')) {
		location[0] -= MOVE_DELTA;
	}

	if (Utils::isKeyPressed('o')) {
		location[1] += MOVE_DELTA;
	}
	else if (Utils::isKeyPressed('l')) {
		location[1] -= MOVE_DELTA;
	}

	if (Utils::isKeyPressed('u')) {
		location[2] += MOVE_DELTA;
	}
	else if (Utils::isKeyPressed('j')) {
		location[2] -= MOVE_DELTA;
	}

	if (Utils::isKeyPressed('y')) {
		SetAttenuation(attenuation - ATTENUATION_DELTA);
	}
	else if (Utils::isKeyPressed('h')) {
		SetAttenuation(attenuation + ATTENUATION_DELTA);
	}
}

void Light::SetAttenuation(GLfloat att)
{
	if (att > MAX_ATTENUATION) attenuation = MAX_ATTENUATION;
	else if (att < 0) attenuation = 0;
	else attenuation = att;
}
