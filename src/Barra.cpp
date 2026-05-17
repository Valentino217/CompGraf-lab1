#include "../headers/Barra.h"

Barra::Barra(float l, float x, float y, float vx, float vy, bool act, float dx)
	: Rect(l, x, y, vx, vy, act, dx)
{
}

void Barra::actualizar(float dt)
{
	if (activo) {
		posicionIzq += velocidadX * dt;
	}
	if (posicionIzq < limiteIzq) {
		posicionIzq = limiteIzq;
		activo = false;
	}
	if (posicionIzq > limiteDer) {
		posicionIzq = limiteDer;
		activo = false;
	}
}
