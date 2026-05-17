#include "../headers/BarraPrisma.h"


void BarraPrisma::actualizar(float dt) {
	if (activo) {
		centroX += velocidadX * dt;
		centroZ += velocidadZ * dt;
		if (centroX < xMin) {
			centroX = xMin;
			activo = false;
		}
		else if (centroX > xMax) {
			centroX = xMax;
			activo = false;
		}
		if (centroZ < zMin) {
			centroZ = zMin;
			activo = false;
		}
		else if (centroZ > zMax) {
			centroZ = zMax;
			activo = false;
		}
	}
}