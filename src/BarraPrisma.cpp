#include "../headers/BarraPrisma.h"


void BarraPrisma::actualizar(float dt) {
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