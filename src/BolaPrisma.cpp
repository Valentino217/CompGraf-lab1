
#include "../headers/BolaPrisma.h"

BolaPrisma::BolaPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act) : Prisma(lx, ly, lz, cx, cy, cz, vx, vz, dx, dz, act) 
{
	cantidad++;
};

void BolaPrisma::setLimites(float xPantalla, float zPantalla) {
	xMin = largoX / 2;
	xMax = xPantalla - largoX / 2;
	zMin = -1 * largoZ / 2;
	zMax = -1 * zPantalla + largoZ / 2;
}

void BolaPrisma::actualizar(float dt)
{
	if (activo) {
		centroX += velocidadX * dt;
		centroZ += velocidadZ * dt;
		if (centroX < xMin) {
			centroX = xMin;
			velocidadX *= -1;
		}
		else if (centroX > xMax) {
			centroX = xMax;
			velocidadX *= -1;
		}
		if (centroZ < zMax) {
			centroZ = zMax;
			velocidadZ *= -1;
		}
		//Si se va de rango acá adelante
		else if (centroZ > zMin) {
			activo = false;
			cantidad--;
			if (cantidad == 0) {
				reset = true;
			}
		}
	}
}

void BolaPrisma::reboteEnemigo() {
	velocidadX *= -1;
	velocidadZ *= -1;
}

void BolaPrisma::reboteBarra() {
	velocidadZ *= -1;
}

int BolaPrisma::cantidad = 0;
bool BolaPrisma::reset = false;