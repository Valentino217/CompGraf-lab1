#include "../headers/Utils.h"
#include "../headers/BarraPrisma.h"
#include "../headers/EnemigoPrisma.h"
#include "../headers/BolaPrisma.h"
#include "../headers/Pantalla.h"
#include <fstream>
#include <vector>
#include "../headers/json.hpp"

using json = nlohmann::json;

void cargaArchivo(std::string nombreArchivo, GameState& juego) {
	//LECTURA DEL ARCHIVO
	std::ifstream archivo(nombreArchivo);
	json carga;
	archivo >> carga;

	juego.pantalla = new Pantalla(carga["pantalla"]["largoX"], carga["pantalla"]["largoY"], carga["pantalla"]["largoZ"]);
	juego.barra = new BarraPrisma(carga["barra"]["largoX"], carga["barra"]["largoY"], carga["barra"]["largoZ"], carga["pantalla"]["largoX"].get<float>() / 2.0, carga["barra"]["largoY"].get<float>() / 2.0, -1 * carga["barra"]["largoZ"].get<float>() / 2.0, carga["barra"]["velocidadX"], 0, carga["pantalla"]["largoX"].get<float>() - carga["barra"]["largoX"].get<float>(), 0, false);
	for (auto& enemigo : carga["posicionesEnemigas"]) {
		juego.enemigos.push_back(EnemigoPrisma(carga["enemigo1"]["largoX"], carga["enemigo1"]["largoY"], carga["enemigo1"]["largoZ"], enemigo["x"], carga["enemigo1"]["largoY"].get<float>() / 2.0, enemigo["z"], carga["enemigo1"]["velocidadX"], carga["enemigo1"]["velocidadZ"], enemigo["deltaX"], enemigo["deltaZ"], false));
	}
	juego.bolas.push_back(BolaPrisma(carga["bola"]["lado"], carga["bola"]["lado"], carga["bola"]["lado"], carga["pantalla"]["largoX"].get<float>() / 2, carga["bola"]["lado"].get<float>() / 2, -1 * carga["barra"]["largoZ"].get<float>() - carga["bola"]["lado"].get<float>() / 2, carga["bola"]["velocidadX"], carga["bola"]["velocidadZ"], carga["pantalla"]["largoX"].get<float>() - carga["bola"]["lado"].get<float>(), 0, false));
	juego.bolas[0].setLimites(carga["pantalla"]["largoX"], carga["pantalla"]["largoZ"]);
}