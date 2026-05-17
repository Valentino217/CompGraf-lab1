#pragma once
#include "BarraPrisma.h"
#include "BolaPrisma.h"
#include "EnemigoPrisma.h"
#include "Pantalla.h"
#include <vector>

class GameState {
public :
	Pantalla* pantalla;
	BarraPrisma* barra;
	std::vector<BolaPrisma> bolas;
	std::vector<EnemigoPrisma> enemigos;

	void limpiar();

	void actualizar(float deltaTiempo);

	void analizarColisiones();
};