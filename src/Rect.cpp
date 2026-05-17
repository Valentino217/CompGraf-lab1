#include "../headers/Rect.h"

#include "../headers/DrawUtils.h"

#include "SDL_opengl.h"

Rect::Rect(float l, float x, float y, float vx, float vy, bool act, float dx)
	: lado(l), posicionIzq(x), posicionSup(y), velocidadX(vx), velocidadY(vy), activo(act), desplazamientoXMax(dx)
{
	limiteIzq = posicionIzq - desplazamientoXMax / 2;
	limiteDer = posicionIzq + desplazamientoXMax / 2;
}

void Rect::actualizar(float)
{
}

void Rect::dibujar() const
{
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(posicionIzq, posicionSup, 0.0f);
	dibujarCubo(lado / 2);
	glPopMatrix();
}
