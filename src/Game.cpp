#include "../headers/Game.h"

#include "../headers/Constantes.h"
#include "../headers/Barra.h"
#include "../headers/Bola.h"
#include "../headers/Colisiones.h"
#include "../headers/Enemigo.h"
#include "../headers/DrawUtils.h"
#include "../headers/GameState.h"
#include "../headers/Prisma.h"
#include "../headers/EnemigoPrisma.h"
#include "../headers/BarraPrisma.h"
#include "../headers/BolaPrisma.h"
#include "../headers/Camara.h"
#include "../headers/Utils.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include <GL/glu.h>
#include <iostream>

int Game::Run()
{
	GameState juego;
	
	cargaArchivo("primerJSon.json", juego);

	std::cout << juego.pantalla->largoX << " " << juego.pantalla->largoY;

	Camara camara(juego.pantalla->largoX, juego.pantalla->largoY);

	bool inicio = false;
	int mousex = 0;
	int mousey = 0;
	int modo = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow(
		"ARKANOID",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		(int)Constantes::LargoVentana, (int)Constantes::AltoVentana,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!win) {
		std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_GLContext context = SDL_GL_CreateContext(win);
	if (!context) {
		std::cerr << "No se pudo crear el contexto OpenGL: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

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
		

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				arkanoid = false;
			}
			if (event.type == SDL_MOUSEMOTION) {
				mousex = event.motion.xrel;
				mousey = event.motion.yrel;
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

		// camara::actualizar(modo, mousex, mousey, barra.posicionIzq, barra.posicionSup);
		camara.actualizar(mousex, mousey, juego.barra->centroX, juego.barra->centroY);
		camara.aplicar();

		tiempoActual = SDL_GetTicks();
		deltaTiempo = (tiempoActual - tiempoInicial) / 1000.0f;
		tiempoInicial = tiempoActual;
		juego.actualizar(deltaTiempo);

		mousex = 0;
		mousey = 0;

		SDL_GL_SwapWindow(win);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
