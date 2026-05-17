#include "../headers/EnemigoPrisma.h"


EnemigoPrisma::EnemigoPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act) : Prisma(lx, ly, lz, cx, cy, cz, vx, vz, dx, dz, act) 
{
	cantidad++;
};

void EnemigoPrisma::actualizar(float dt) {
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
		if (centroZ < zMin) {
			centroZ = zMin;
			velocidadZ *= -1;
		}
		else if (centroZ > zMax) {
			centroZ = zMax;
			velocidadZ *= -1;
		}
	}
}

int EnemigoPrisma::cantidad = 0;