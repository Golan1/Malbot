#pragma once
#include "Drawable.h"
class Rect : public Drawable
{
public:
	Vector3d size;

	Rect(Vector3d size, bool isSolid = true);
	~Rect();

	virtual void Init();
	virtual void Draw();

private:	
	bool _isSolid;
};

