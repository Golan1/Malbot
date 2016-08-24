#pragma once
#include "Rect.h"
class Body :
	public Rect
{
public:
	Body(Vector3f size);
	~Body();
};

