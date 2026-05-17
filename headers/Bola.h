#pragma once


class Bola
{
public:
	float centroX, centroY;
	float velocidadX, velocidadY;
	float radio;

	Bola(float x, float y, float vx, float vy, float r);

	void actualizar(float dt, float largoVentana, float altoVentana);
	void dibujar() const;
};
