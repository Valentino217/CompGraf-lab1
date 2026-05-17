#pragma once

class Prisma
{
public:
	float largoX, largoY, largoZ;
	float centroX, centroY, centroZ;
	float velocidadXMax, velocidadZMax;
	float velocidadX, velocidadZ;
	float deltaXMax, deltaZMax;
	float xMin, xMax, zMin, zMax;
	bool activo;
	bool visible;

	Prisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act);

	virtual ~Prisma() = default;
	virtual void actualizar(float dt);
	void dibujar() const;
	bool colision(Prisma& otro) const;
};
