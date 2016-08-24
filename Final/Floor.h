#pragma once
#include "Drawable.h"
#include "Texture2D.h"
class Floor :
	public Drawable
{
public:
	Floor(int size);
	~Floor();
	void Init();

private:
	int _size;
	Texture2D* _texture;
};

