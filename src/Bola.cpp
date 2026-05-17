#include "../headers/Bola.h"

#include "SDL_opengl.h"

#include <cmath>

Bola::Bola(float x, float y, float vx, float vy, float r)
	: centroX(x), centroY(y), velocidadX(vx), velocidadY(vy), radio(r)
{
}

void Bola::actualizar(float dt, float largoVentana, float altoVentana)
{
	centroX += velocidadX * dt;
	centroY += velocidadY * dt;
	if (centroX < radio) {
		centroX = radio;
		velocidadX = -1 * velocidadX;
	}
	if (centroX > largoVentana - radio) {
		centroX = largoVentana - radio;
		velocidadX = -1 * velocidadX;
	}
	if (centroY < radio) {
		centroY = radio;
		velocidadY = -1 * velocidadY;
	}
	if (centroY > altoVentana - radio) {
		centroY = altoVentana - radio;
		velocidadY = -1 * velocidadY;
	}
}

void Bola::dibujar() const
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 1, 0);
	glVertex2f(centroX, centroY);
	for (int i = 0; i <= 20; i++) {
		float angulo = i * 2.0f * 3.14159f / 20.0f;
		float verticeX = centroX + std::cos(angulo) * radio;
		float verticeY = centroY + std::sin(angulo) * radio;
		glVertex2f(verticeX, verticeY);
	}
	glEnd();
}
