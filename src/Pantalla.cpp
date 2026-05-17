#include "../headers/Pantalla.h"

Pantalla::Pantalla(float x, float y, float z) : largoX(x), largoY(y), largoZ(z) {
	centroX = largoX / 2.0;
	centroY = largoY / 2.0;
	centroZ = largoZ / 2.0;
};