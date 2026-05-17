#include "../headers/GameState.h"

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