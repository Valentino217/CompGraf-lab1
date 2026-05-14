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
