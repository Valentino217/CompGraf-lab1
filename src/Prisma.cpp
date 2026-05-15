#include "../headers/Prisma.h"

#include "../headers/DrawUtils.h"

#include "SDL_opengl.h"

#include <cmath>

//Constructor
Prisma::Prisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act)
	: largoX(lx), largoY(ly), largoZ(lz), centroX(cx), centroY(cy), centroZ(cz), velocidadX(vx), velocidadZ(vz), activo(act), desplazamientoXMax(dx), desplazamientoZMax(dz)
{
	xMin = centroX - desplazamientoXMax / 2;
	xMax = centroX + desplazamientoXMax / 2;
	zMin = centroZ - desplazamientoZMax / 2;
	zMax = centroZ + desplazamientoZMax / 2;
}

void Prisma::actualizar(float)
{
}

void Prisma::dibujar() const
{
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(centroX, centroY, centroZ);
	dibujarPrisma(largoX, largoY, largoZ);
	glPopMatrix();
}