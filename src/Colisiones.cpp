#include "../headers/Colisiones.h"

#include "../headers/Bola.h"
#include "../headers/Barra.h"

void colisionBarraBola(Bola& bola, Barra& barra)
{
	if (bola.centroX + bola.radio >= barra.posicionIzq && bola.centroX - bola.radio <= barra.posicionIzq + barra.lado) {
		if (bola.centroY + bola.radio >= barra.posicionSup && bola.centroY - bola.radio <= barra.posicionSup + barra.lado) {
			bola.velocidadY = -1 * bola.velocidadY;
			if (barra.velocidadX * bola.velocidadX < 0) {
				bola.velocidadX = -1 * bola.velocidadX;
			}
		}
	}
}
