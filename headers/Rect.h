#pragma once

class Rect
{
public:
	float lado;
	float posicionIzq, posicionSup;
	float velocidadX, velocidadY;
	bool activo;
	float desplazamientoXMax;
	float limiteIzq, limiteDer;

	Rect(float l, float x, float y, float vx, float vy, bool act, float dx);
	virtual ~Rect() = default;

	virtual void actualizar(float dt);
	void dibujar() const;
};
