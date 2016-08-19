#pragma once
#include "Rect.h"
class Body :
	public Rect
{
public:
	Body(Vector3d size);
	~Body();
};

