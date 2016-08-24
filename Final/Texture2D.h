#pragma once
#include "Utils.h"

class Texture2D
{
public:
	Texture2D(char* filename);
	~Texture2D();
	void Init();
	void Enable();
	void Disable();

private:
	int _width, _height;
	GLuint _id;
	void* _rescaledImageData;
};

