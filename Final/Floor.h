#pragma once
#include "Drawable.h"
#include "Texture2D.h"
#include "Material.h"
class Floor :
	public Drawable
{
public:
	Floor(GLint size);
	~Floor();
	void Init();

private:
	int _size;
	Texture2D* _texture;
	Material* _material;
};

