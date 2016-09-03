#pragma once
#include "Drawable.h"
#include "Texture2D.h"
#include "Material.h"

// Handling the floor object
// The floor is made of multiple instanses of the same object
class Floor :
	public Drawable
{
public:
	// Choose size
	Floor(GLint size);
	~Floor();

	void Init();

private:
	int _size;
	Texture2D* _texture;
	Material* _material;
};

