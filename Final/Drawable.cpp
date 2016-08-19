#pragma once
#include "Drawable.h"

Drawable::Drawable()
{
}

Drawable::~Drawable()
{
}

void Drawable::Draw()
{
	glCallList(_listId);
}
