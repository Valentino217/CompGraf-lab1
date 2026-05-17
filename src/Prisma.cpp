#include "../headers/Prisma.h"
#include "../headers/DrawUtils.h"
#include "SDL_opengl.h"

#include <cmath>

//Constructor
Prisma::Prisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act)
	: largoX(lx), largoY(ly), largoZ(lz), centroX(cx), centroY(cy), centroZ(cz), velocidadXMax(vx), velocidadZMax(vz), velocidadX(vx), velocidadZ(vz), activo(act), deltaXMax(dx), deltaZMax(dz)
{
	xMin = centroX - deltaXMax / 2;
	xMax = centroX + deltaXMax / 2;
	zMin = centroZ - deltaZMax / 2;
	zMax = centroZ + deltaZMax / 2;
	visible = true;
}

void Prisma::actualizar(float) {}

void Prisma::dibujar() const
{
	if (visible) {
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(centroX, centroY, centroZ);
		dibujarPrisma(largoX, largoY, largoZ);
		glPopMatrix();
	}
}

bool Prisma::colision(Prisma& otro) const 
{
	if (centroX + largoX / 2 > otro.centroX - otro.largoX / 2 &&
		centroX - largoX / 2 < otro.centroX + otro.largoX / 2 &&
		centroY + largoY / 2 > otro.centroY - otro.largoY / 2 &&
		centroY - largoY / 2 < otro.centroY + otro.largoY / 2 &&
		centroZ + largoZ / 2 > otro.centroZ - otro.largoZ / 2 &&
		centroZ - largoZ / 2 < otro.centroZ + otro.largoZ / 2) {
		return true;
	}
	return false;
}