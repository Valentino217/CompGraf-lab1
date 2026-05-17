#include "../headers/GameState.h"
#include <iostream>

void GameState::limpiar() {
	delete barra;
	barra = nullptr;

	bolas.clear();
	enemigos.clear();
}

void GameState::actualizar(float deltaTiempo) {
	barra->actualizar(deltaTiempo);
	barra->dibujar();

	//DIBUJAR LA PELOTA
	for (BolaPrisma& bola : bolas) {
		bola.actualizar(deltaTiempo);
		bola.dibujar();
	}
	for (EnemigoPrisma& enemigo : enemigos) {
		enemigo.actualizar(deltaTiempo);
		enemigo.dibujar();
	}
}

void GameState::analizarColisiones() {
	for (auto& bola : bolas) {
		for (auto& enemigo : enemigos) {
			if (enemigo.visible && bola.colision(enemigo)) {
				std::cout << "enemigo";
				enemigo.activo = false;
				enemigo.visible = false;
				//AGREGAR UNA EXPLOSION
				bola.reboteEnemigo();
			}
		}
		if (bola.colision(*barra)) {
			bola.reboteBarra();
		}
	}
}