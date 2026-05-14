#include "../headers/Enemigo.h"

Enemigo::Enemigo(float l, float x, float y, float vx, float vy, bool act, float dx)
	: Rect(l, x, y, vx, vy, act, dx)
{
}

void Enemigo::actualizar(float dt)
{
	if (activo) {
		posicionIzq += velocidadX * dt;
	}
	if (posicionIzq < limiteIzq) {
		posicionIzq = limiteIzq;
		velocidadX = -1 * velocidadX;
	}
	if (posicionIzq > limiteDer) {
		posicionIzq = limiteDer;
		velocidadX = -1 * velocidadX;
	}
}
