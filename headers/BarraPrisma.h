#pragma once


#include "Prisma.h"


class BarraPrisma : public Prisma
{
public:

	BarraPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act) : Prisma(lx, ly, lz, cx, cy, cz, vx, vz, dx, dz, act) {};

	void actualizar(float dt);

};