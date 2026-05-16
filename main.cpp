#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

//DEFINICION DE FUNCIONES
void dibujarPrisma(float x, float y, float z) {
	glBegin(GL_QUADS);
	x = x / 2;
	y = y / 2;
	z = z / 2;

	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(-x, y, -z);

	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);

	glVertex3f(x, -y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);

	glVertex3f(-x, -y, z);
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);

	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);

	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, -y, z);

	glEnd();
}

class Prisma {
public :
	float largoX, largoY, largoZ;
	float centroX, centroY, centroZ;
	float velocidadXMax, velocidadZMax;
	float velocidadX, velocidadZ;
	float deltaXMax, deltaZMax;
	float xMin, xMax, zMin, zMax;
	bool activo;
	
	Prisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act) {
		largoX = lx;
		largoY = ly;
		largoZ = lz;
 		centroX = cx;
		centroY = cy;
		centroZ = cz;
		velocidadXMax = vx;
		velocidadZMax = vz;
		velocidadX = vx;
		velocidadZ = vz;
		deltaXMax = dx;
		deltaZMax = dz;
		xMin = centroX - deltaXMax / 2;
		xMax = centroX + deltaXMax / 2;
		zMin = centroZ - deltaZMax / 2;
		zMax = centroZ + deltaZMax / 2;
		activo = act;
	}

	void dibujar() {
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(centroX, centroY, centroZ);
		dibujarPrisma(largoX, largoY, largoZ);
		glPopMatrix();
	}

	bool colision(Prisma& otro) {
		if (centroX + largoX / 2 > otro.centroX - otro.largoX / 2 &&
			centroX - largoX / 2 < otro.centroX + otro.largoX / 2 &&
			centroY + largoY / 2 > otro.centroY - otro.largoY / 2 &&
			centroY - largoY / 2 > otro.centroY + otro.largoY / 2 &&
			centroZ + largoZ / 2 > otro.centroZ - otro.largoZ / 2 &&
			centroZ - largoZ / 2 > otro.centroZ + otro.largoZ / 2) {
			return true;
		}
		return false;
	}
};

class EnemigoPrisma : public Prisma {
public:
	static int cantidad;

	EnemigoPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act) : Prisma(lx, ly, lz, cx, cy, cz, vx, vz, dx, dz, act) {
		cantidad++;
	};
	
	void actualizar(float dt) {
		if (activo) {
			centroX += velocidadX * dt;
			centroZ += velocidadZ * dt;
			if (centroX < xMin) {
				centroX = xMin;
				velocidadX *= -1;
			}
			else if (centroX > xMax) {
				centroX = xMax;
				velocidadX *= -1;
			}
			if (centroZ < zMin) {
				centroZ = zMin;
				velocidadZ *= -1;
			}
			else if (centroZ > zMax) {
				centroZ = zMax;
				velocidadZ *= -1;
			}
		}
	}
};

class BarraPrisma : public Prisma {
public:
	BarraPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act) : Prisma(lx, ly, lz, cx, cy, cz, vx, vz, dx, dz, act) {};

	void actualizar(float dt) {
		if (activo) {
			centroX += velocidadX * dt;
			centroZ += velocidadZ * dt;
			if (centroX < xMin) {
				centroX = xMin;
				activo = false;
			}
			else if (centroX > xMax) {
				centroX = xMax;
				activo = false;
			}
			if (centroZ < zMin) {
				centroZ = zMin;
				activo = false;
			}
			else if (centroZ > zMax) {
				centroZ = zMax;
				activo = false;
			}
		}
	}
};

class BolaPrisma : public Prisma {
public :
	static bool reset;
	static int cantidad;

	BolaPrisma(float lx, float ly, float lz, float cx, float cy, float cz, float vx, float vz, float dx, float dz, bool act) : Prisma(lx, ly, lz, cx, cy, cz, vx, vz, dx, dz, act) { 
		cantidad++;
	};

	void setLimites(float xPantalla, float zPantalla) {
		xMin = largoX / 2;
		xMax = xPantalla - largoX / 2;
		zMin = -1 * largoZ / 2;
		zMax = -1 * zPantalla + largoZ / 2;
	}
	
	void actualizar(float dt) {
		if (activo) {
			centroX += velocidadX * dt;
			centroZ += velocidadZ * dt;
			if (centroX < xMin) {
				centroX = xMin;
				velocidadX *= -1;
			}
			else if (centroX > xMax) {
				centroX = xMax;
				velocidadX *= -1;
			}
			if (centroZ < zMax) {
				std::cout << "puta";
				centroZ = zMax;
				velocidadZ *= -1;
			}
			//Si se va de rango acá adelante
			else if (centroZ > zMin) {
				std::cout << "madre";
				activo = false;
				cantidad--;
				if (cantidad == 0) {
					reset = true;
				}
			}
		}
	}
};

class Pantalla {
public :
	float largoX, largoY, largoZ;
	float centroX, centroY, centroZ;

	Pantalla(float x, float y, float z) {
		largoX = x;
		largoY = y;
		largoZ = z;
		centroX = largoX / 2.0;
		centroY = largoY / 2.0;
		centroZ = largoZ / 2.0;
	}
};

//DEFINICION DE LOS VALORES INICIALES DE LOS STATIC
int EnemigoPrisma::cantidad = 0;
int BolaPrisma::cantidad = 0;
bool BolaPrisma::reset = false;

//DEFINICIONES PARA EL MAIN
class GameState {
public :
	Pantalla* pantalla;
	BarraPrisma* barra;
	std::vector<BolaPrisma> bolas;
	std::vector<EnemigoPrisma> enemigos;

	void limpiar() {
		delete barra;
		barra = nullptr;

		bolas.clear();
		enemigos.clear();
	}

	void actualizar(float deltaTiempo) {
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
};

GameState juego;

json leerArchivoJson(std::string nombreArchivo) {
	std::ifstream archivo(nombreArchivo);
	json carga;
	archivo >> carga;
	return carga;
}

void cargaArchivo(std::string nombreArchivo) {
	//LECTURA DEL ARCHIVO
	std::ifstream archivo(nombreArchivo);
	json carga;
	archivo >> carga;

	juego.pantalla = new Pantalla(carga["pantalla"]["largoX"], carga["pantalla"]["largoY"], carga["pantalla"]["largoZ"]);
	juego.barra = new BarraPrisma(carga["barra"]["largoX"], carga["barra"]["largoY"], carga["barra"]["largoZ"], carga["pantalla"]["largoX"].get<float>() / 2.0, carga["barra"]["largoY"].get<float>() / 2.0, -1 * carga["barra"]["largoZ"].get<float>() / 2.0, carga["barra"]["velocidadX"], 0, carga["pantalla"]["largoX"].get<float>() - carga["barra"]["largoX"].get<float>(), 0, false);
	for (auto& enemigo : carga["posicionesEnemigas"]) {
		juego.enemigos.push_back(EnemigoPrisma(carga["enemigo1"]["largoX"], carga["enemigo1"]["largoY"], carga["enemigo1"]["largoZ"], enemigo["x"], carga["enemigo1"]["largoY"].get<float>(), enemigo["z"], carga["enemigo1"]["velocidadX"], carga["enemigo1"]["velocidadZ"], enemigo["deltaX"], enemigo["deltaZ"], false));
	}
	juego.bolas.push_back(BolaPrisma(carga["bola"]["lado"], carga["bola"]["lado"], carga["bola"]["lado"], carga["pantalla"]["largoX"].get<float>() / 2, carga["bola"]["lado"].get<float>() / 2, -1 * carga["barra"]["largoZ"].get<float>() - carga["bola"]["lado"].get<float>() / 2, carga["bola"]["velocidadX"], carga["bola"]["velocidadZ"], carga["pantalla"]["largoX"].get<float>() - carga["bola"]["lado"].get<float>(), 0, false));
	juego.bolas[0].setLimites(carga["pantalla"]["largoX"], carga["pantalla"]["largoZ"]);
}

int main(int argc, char* argv[]) {
	cargaArchivo("primerJSon.json");
	
	bool inicio = false;

	std::cout << juego.enemigos[0].centroX << " " << juego.enemigos[1].centroY << " " << juego.enemigos[2].centroZ;

	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	//CREAR VENTANA
	SDL_Window* win = SDL_CreateWindow(
		"ARKANOID",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		juego.pantalla->largoX, juego.pantalla->largoY,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	SDL_GLContext context = SDL_GL_CreateContext(win);

	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);

	gluPerspective(45, juego.pantalla->largoX / juego.pantalla->largoY, 0.1, juego.pantalla->largoZ * 2.5);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	bool arkanoid = true;
	SDL_Event event;
	Uint32 tiempoInicial = SDL_GetTicks();
	Uint32 tiempoActual = tiempoInicial;
	float deltaTiempo = 0.0f;

	while (arkanoid) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(juego.pantalla->centroX, juego.pantalla->centroY, juego.pantalla->largoZ, juego.pantalla->centroX, juego.pantalla->centroY, 0, 0, 1, 0);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				arkanoid = false;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					juego.barra->velocidadX = juego.barra->velocidadXMax * -1;
					juego.barra->activo = true;
					if (!inicio) {
						inicio = true;
						juego.bolas[0].velocidadX *= -1;
						juego.bolas[0].activo = true;
						for (auto& enemigo : juego.enemigos) {
							enemigo.activo = true;
						}
					}
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					juego.barra->velocidadX = juego.barra->velocidadXMax;
					juego.barra->activo = true;
					if (!inicio) {
						inicio = true;
						std::cout << juego.bolas[0].centroZ << " " << juego.bolas[0].velocidadZ << " " << juego.bolas[0].zMax << " " << juego.bolas[0].zMin << std::endl;
						juego.bolas[0].activo = true;
						for (auto& enemigo : juego.enemigos) {
							enemigo.activo = true;
						}
					}
				}
			}
			if (event.type == SDL_KEYUP) {
				juego.barra->activo = false;
			}
		}
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Funcion para activar el wireframe, comentar para ver los cubos solidos

		tiempoActual = SDL_GetTicks();
		deltaTiempo = (tiempoActual - tiempoInicial) / 1000.0f;
		tiempoInicial = tiempoActual;

		juego.actualizar(deltaTiempo);
		
		SDL_GL_SwapWindow(win);
	}

	return 0;
}

/*
//DECLARACION DE CONSTANTES
//DIMENSIONES
float largoVentana = 640;
float altoVentana = 480;
float barraAlto = 10;
float barraLargo = 100;
float bolaRadio = 10;
float enemigoLargo = 40;
float enemigoAlto = 40;

//POSICIONES
float centroVentanaX = largoVentana / 2; //320
float barraX =  centroVentanaX; //320 - 50 = 270
float barraY = 0 + barraAlto;
float bolaCentroX = centroVentanaX;
float bolaCentroY = barraLargo + bolaRadio;
float enemigo1X = largoVentana / 3 - enemigoLargo / 2;
float enemigo2X = largoVentana / 2 - enemigoLargo / 2;
float enemigo3X = 2 * largoVentana / 3 - enemigoLargo / 2;
float enemigo1Y = 2 * altoVentana / 3 - enemigoAlto / 2;
float enemigo2Y = 1.75 * altoVentana / 2 - enemigoAlto / 2;
float enemigo3Y = 2 * altoVentana / 3 - enemigoAlto / 2;

//VELOCIDADES
float velocidadBolaX = 150;
float velocidadBolaY = 200;
float velocidadBarraX = 400;
float velocidadBarraY = 0;
float velocidadEnemigo1X = 200;
float velocidadEnemigo2X = 300;
float velocidadBolaMinimaY = 50;

//DESPLAZAMIENTOS
float barraDX = largoVentana - barraLargo;
float enemigo1DX = 200;
float enemigo2DX = 300;

void dibujarCubo(float s) {

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

//DEFINICION DE CLASES
class Bola {
public :
	float centroX, centroY;
	float velocidadX, velocidadY;
	float radio;
	
	Bola(float x, float y, float vx, float vy, float r) {
		centroX = x;
		centroY = y;
		velocidadX = vx;
		velocidadY = vy;
		radio = r;
	}

	void inicio() {
		velocidadX = velocidadBolaX;
		velocidadY = velocidadBolaY;
	}

	void actualizar(float dt) {
		centroX += velocidadX * dt;
		centroY += velocidadY * dt;
		if (centroX < radio) {
			centroX = radio;
			velocidadX = -1 * velocidadX;
		}
		if (centroX > largoVentana - radio) {
			centroX = largoVentana - radio;
			velocidadX = -1 * velocidadX;
		}
		if (centroY < radio) {
			centroY = radio;
			velocidadY = -1 * velocidadY;
		}
		if (centroY > altoVentana - radio) {
			centroY = altoVentana - radio;
			velocidadY = -1 * velocidadY;
		}
	}
	
	void dibujar() {
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0, 1, 0);
		glVertex2f(centroX, centroY);
		for (int i = 0; i <= 20; i++) {
			float angulo = i * 2.0 * 3.14159f / 20;
			float verticeX = centroX + cos(angulo) * radio;
			float verticeY = centroY + sin(angulo) * radio;
			glVertex2f(verticeX, verticeY);
		}
		glEnd();
	}
};

class Rect {
public :
	float lado;
	float posicionIzq, posicionSup;
	float velocidadX, velocidadY;
	bool activo;
	float desplazamientoXMax;
	float limiteIzq, limiteDer;

	Rect(float l, float x, float y, float vx, float vy, bool act, float dx) {
		lado = l;
		posicionIzq = x;
		posicionSup = y;
		velocidadX = vx;
		velocidadY = vy;
		activo = act;
		desplazamientoXMax = dx;
		limiteIzq = posicionIzq - desplazamientoXMax / 2;
		limiteDer = posicionIzq + desplazamientoXMax / 2;
	}

	virtual void actualizar(float dt) {} ;
	
	void dibujar() {
		glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glTranslatef(posicionIzq, posicionSup, 0.0f);
		// Si 'lado' es 40, el cubo será visible.
		dibujarCubo(lado / 2);
		glPopMatrix();
	}
};
class Enemigo : public Rect {
public:
	Enemigo(float l, float x, float y, float vx, float vy, bool act, float dx) : Rect(l, x, y, vx, vy, act, dx) {};

	void actualizar(float dt) {
		if (activo) {
			posicionIzq += velocidadX * dt;
		}
		if (posicionIzq < limiteIzq) {
			posicionIzq = limiteIzq;
			velocidadX = -1 * velocidadX;
		}
		if (posicionIzq > limiteDer) {
			posicionIzq = limiteDer;
			velocidadX = -1 * velocidadX;
		}
	}
};

class Barra : public Rect {
public:
	Barra(float l, float x, float y, float vx, float vy, bool act, float dx) : Rect(l, x, y, vx, vy, act, dx) {};

	void actualizar(float dt) {
		if (activo) {
			posicionIzq += velocidadX * dt;
		}
		if (posicionIzq < limiteIzq) {
			posicionIzq = limiteIzq;
			activo = false;
		}
		if (posicionIzq > limiteDer) {
			posicionIzq = limiteDer;
			activo = false;
		}
	}
};

int main(int argc, char *argv[]) {

	BolaPrisma bola2(50, 50, 50, 300, 300, 100, 100, 50, 200, 200, true);
	EnemigoPrisma enemigo4(100, 200, 50, 200, 200, 200, 100, 100, 200, 100, true);
	Bola bola(bolaCentroX, bolaCentroY, 0, 0, bolaRadio);
	Barra barra(barraLargo, barraX, barraY, velocidadBarraX, velocidadBarraY, false, barraDX);
	Enemigo enemigo1(enemigoLargo, enemigo1X, enemigo1Y, velocidadEnemigo1X, 0, true, enemigo1DX);
	Enemigo enemigo2(enemigoLargo, enemigo2X, enemigo2Y, velocidadEnemigo2X, 0, true, enemigo2DX);
	Enemigo enemigo3(enemigoLargo, enemigo3X, enemigo3Y, velocidadEnemigo1X, 0, true, enemigo1DX);

	bool inicio = false;

	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}
	
	//CREAR VENTANA
	SDL_Window* win = SDL_CreateWindow(
		"ARKANOID",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		largoVentana, altoVentana, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
	SDL_GLContext context = SDL_GL_CreateContext(win);

	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);

	gluPerspective(45, 640 / 480.f, 0.1, 1000);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	bool arkanoid = true;
	SDL_Event event;
	Uint32 tiempoInicial = SDL_GetTicks();
	Uint32 tiempoActual = tiempoInicial;
	float deltaTiempo = 0.0f;

	while (arkanoid) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(320, 240, 600, 320, 240, 0, 0, 1, 0);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				arkanoid = false;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					barra.activo = true;
					barra.velocidadX = -1 * velocidadBarraX;
					if (!inicio) {
						inicio = true;
						bola.velocidadX = -1 * velocidadBolaX;
						bola.velocidadY = -1 * velocidadBolaY;
					}
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					barra.activo = true;
					barra.velocidadX = velocidadBarraX;
					if (!inicio) {
						inicio = true;
						bola.velocidadX = velocidadBolaX;
						bola.velocidadY = -1 * velocidadBolaY;
					}
				}
			}
			if (event.type == SDL_KEYUP) {
				barra.activo = false ;
			}
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Funcion para activar el wireframe, comentar para ver los cubos solidos
		
		tiempoActual = SDL_GetTicks();
		deltaTiempo = (tiempoActual - tiempoInicial) / 1000.0f;
		tiempoInicial = tiempoActual;
		
		barra.actualizar(deltaTiempo);
		barra.dibujar();

		//DIBUJAR LA PELOTA
		bola.actualizar(deltaTiempo);
		bola.dibujar();

		//DIBUJAR ENEMIGOS
		enemigo1.actualizar(deltaTiempo);
		enemigo1.dibujar();

		enemigo2.actualizar(deltaTiempo);
		enemigo2.dibujar();

		enemigo3.actualizar(deltaTiempo);
		enemigo3.dibujar();

		enemigo4.actualizar(deltaTiempo);
		enemigo4.dibujar();

		bola2.actualizar(deltaTiempo);
		bola2.dibujar();

		if (inicio) {
			colisionBarraBola(bola, barra);
		}
		
		SDL_GL_SwapWindow(win);
	}

	return 0;
}
*/


/*

	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);

	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	//TEXTURA
	char* archivo = new char[20];
	archivo = "../canon.png";

	//CARGAR IMAGEN
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(archivo);
	FIBITMAP* bitmap = FreeImage_Load(fif, archivo);
	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	int w = FreeImage_GetWidth(bitmap);
	int h = FreeImage_GetHeight(bitmap);
	void* datos = FreeImage_GetBits(bitmap);
	//FIN CARGAR IMAGEN

	GLuint textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, datos);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//FIN TEXTURA


	bool fin = false;
	bool rotate = false;

	SDL_Event evento;

	float x, y, z;

	x = 0;
	y = 0;
	z = 7;
	float degrees = 0;

	GLfloat luz_posicion[4] = { 0, 0, 1, 1 };
	GLfloat luz_posicion1[4] = { 0, 0, -1, 1 };
	GLfloat colorLuz[4] = { 1, 1, 1, 1 };
	//FIN INICIALIZACION
	bool textOn = true;

	//LOOP PRINCIPAL
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

		//PRENDO LA LUZ (SIEMPRE DESPUES DEL gluLookAt)
		glEnable(GL_LIGHT0); // habilita la luz 0
		glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, colorLuz);

		glEnable(GL_LIGHT1); // habilita la luz 1
		glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, colorLuz);

		glPushMatrix();
		//TRANSFORMACIONES LINEALES
		if (rotate){
			degrees = degrees + 1;
		}
		glRotatef(degrees, 0.0, 1.0, 0.0);

		//DIBUJAR OBJETOS
		//DIBUJO TRIANGULO CON COLOR
		glBegin(GL_TRIANGLES);
			glColor3f(1.0, 0.0, 0.0);
			glVertex3f(1., -1., 0.);
			glVertex3f(-1., -1., 0.);
			glVertex3f(0., 1., 0.);
		glEnd();
		glPopMatrix();

		//DIBUJO TRIANGULO CON TEXTURA
		if (textOn){
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textura);
		}
		glBegin(GL_TRIANGLES);
			glColor3f(1.0, 1.0, 1.0);
			glTexCoord2f(0, 0);
			glVertex3f(3., -1., 0.);
			glTexCoord2f(0, 1);
			glVertex3f(1., -1., 0.);
			glTexCoord2f(1, 0);
			glVertex3f(2., 1., 0.);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//DIBUJO TRIANGULO CON LUZ
		glEnable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
			glNormal3f(0, 0, 1);
			glVertex3f(-1., -1., 0.);
			glVertex3f(-3., -1., 0.);
			glVertex3f(-2., 1., 0.);
		glEnd();
		glDisable(GL_LIGHTING);


		//FIN DIBUJAR OBJETOS

		//MANEJO DE EVENTOS
		while (SDL_PollEvent(&evento)){
			switch (evento.type) {
			case SDL_MOUSEBUTTONDOWN:
				rotate = true;
				cout << "ROT\n";
				break;
			case SDL_MOUSEBUTTONUP:
				rotate = false;
				break;
			case SDL_QUIT:
				fin = true;
				break;
			case SDL_KEYUP:
				switch (evento.key.keysym.sym) {
				case SDLK_ESCAPE:
					fin = true;
					break;
				case SDLK_l:
					textOn = !textOn;
					break;
				case SDLK_RIGHT:
					break;
				}
			}
		}
		//FIN MANEJO DE EVENTOS
		SDL_GL_SwapWindow(win);
	} while (!fin);
	//FIN LOOP PRINCIPAL
	// LIMPIEZA
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();

*/