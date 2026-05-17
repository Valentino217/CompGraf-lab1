#pragma once

#include "Prisma.h"

class BolaPrisma : public Prisma
{
public:
	static bool reset;
	static int cantidad;

	BolaPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act);

	void setLimites(float xPantalla, float zPantalla);
	void actualizar(float dt);
};