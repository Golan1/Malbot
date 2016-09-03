#pragma once
#include "Drawable.h"

//Basic cube
class Rect : public Drawable
{
public:
	Vector3f size;

	Rect(Vector3f size, bool isSolid = true);
	~Rect();

	virtual void Init();
	virtual void Draw();

private:	
	bool _isSolid;
};

