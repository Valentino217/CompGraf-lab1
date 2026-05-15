#include "../headers/DrawUtils.h"

#include "SDL_opengl.h"

void dibujarCubo(float s)
{
	glBegin(GL_QUADS);
	// Cara Frontal
	glVertex3f(-s, -s, s);
	glVertex3f(s, -s, s);
	glVertex3f(s, s, s);
	glVertex3f(-s, s, s);

	// Cara Trasera
	glVertex3f(-s, -s, -s);
	glVertex3f(-s, s, -s);
	glVertex3f(s, s, -s);
	glVertex3f(s, -s, -s);

	// Cara Superior
	glVertex3f(-s, s, -s);
	glVertex3f(-s, s, s);
	glVertex3f(s, s, s);
	glVertex3f(s, s, -s);

	// Cara Inferior
	glVertex3f(-s, -s, -s);
	glVertex3f(s, -s, -s);
	glVertex3f(s, -s, s);
	glVertex3f(-s, -s, s);

	// Cara Derecha
	glVertex3f(s, -s, -s);
	glVertex3f(s, s, -s);
	glVertex3f(s, s, s);
	glVertex3f(s, -s, s);

	// Cara Izquierda
	glVertex3f(-s, -s, -s);
	glVertex3f(-s, -s, s);
	glVertex3f(-s, s, s);
	glVertex3f(-s, s, -s);
	glEnd();
}

void dibujarPrisma(float lx, float ly, float lz)
{
	float hx = lx / 2.0f;
	float hy = ly / 2.0f;
	float hz = lz / 2.0f;

	glBegin(GL_QUADS);
	// Cara frontal (+Z)
	glVertex3f(-hx, -hy, hz);
	glVertex3f(hx, -hy, hz);
	glVertex3f(hx, hy, hz);
	glVertex3f(-hx, hy, hz);

	// Cara trasera (-Z)
	glVertex3f(-hx, -hy, -hz);
	glVertex3f(-hx, hy, -hz);
	glVertex3f(hx, hy, -hz);
	glVertex3f(hx, -hy, -hz);

	// Cara superior (+Y)
	glVertex3f(-hx, hy, -hz);
	glVertex3f(-hx, hy, hz);
	glVertex3f(hx, hy, hz);
	glVertex3f(hx, hy, -hz);

	// Cara inferior (-Y)
	glVertex3f(-hx, -hy, -hz);
	glVertex3f(hx, -hy, -hz);
	glVertex3f(hx, -hy, hz);
	glVertex3f(-hx, -hy, hz);

	// Cara derecha (+X)
	glVertex3f(hx, -hy, -hz);
	glVertex3f(hx, hy, -hz);
	glVertex3f(hx, hy, hz);
	glVertex3f(hx, -hy, hz);

	// Cara izquierda (-X)
	glVertex3f(-hx, -hy, -hz);
	glVertex3f(-hx, -hy, hz);
	glVertex3f(-hx, hy, hz);
	glVertex3f(-hx, hy, -hz);
	glEnd();
}
