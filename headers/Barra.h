#pragma once

#include "Rect.h"

class Barra : public Rect
{
public:
	Barra(float l, float x, float y, float vx, float vy, bool act, float dx);
	void actualizar(float dt) override;
};
