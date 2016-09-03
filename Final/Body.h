#pragma once
#include "Rect.h"

// The robot's body
class Body :
	public Rect
{
public:
	Body(Vector3f size);
	~Body();
};

