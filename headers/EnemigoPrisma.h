#pragma once

#include "Prisma.h"

class EnemigoPrisma : public Prisma
{
public:
	static int cantidad;

	EnemigoPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act);

	void actualizar(float dt);
};