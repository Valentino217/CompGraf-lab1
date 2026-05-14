#pragma once

#include "Rect.h"


class Enemigo : public Rect
{
public:
	Enemigo(float l, float x, float y, float vx, float vy, bool act, float dx);
	void actualizar(float dt) override;
};
