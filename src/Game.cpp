#include "../headers/Game.h"

#include "../headers/Constantes.h"
#include "../headers/Barra.h"
#include "../headers/Bola.h"
#include "../headers/Colisiones.h"
#include "../headers/Enemigo.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include <GL/glu.h>
#include <iostream>

int Game::Run()
{
	Bola bola(Constantes::BolaCentroX, Constantes::BolaCentroY, 0, 0, Constantes::BolaRadio);
	Barra barra(Constantes::BarraLargo, Constantes::BarraX, Constantes::BarraY, Constantes::VelocidadBarraX, Constantes::VelocidadBarraY, false, Constantes::BarraDX);
	Enemigo enemigo1(Constantes::EnemigoLargo, Constantes::Enemigo1X, Constantes::Enemigo1Y, Constantes::VelocidadEnemigo1X, 0, true, Constantes::Enemigo1DX);
	Enemigo enemigo2(Constantes::EnemigoLargo, Constantes::Enemigo2X, Constantes::Enemigo2Y, Constantes::VelocidadEnemigo2X, 0, true, Constantes::Enemigo2DX);
	Enemigo enemigo3(Constantes::EnemigoLargo, Constantes::Enemigo3X, Constantes::Enemigo3Y, Constantes::VelocidadEnemigo1X, 0, true, Constantes::Enemigo1DX);

	bool inicio = false;

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

	glMatrixMode(GL_PROJECTION);
	float color = 0;
	glClearColor(color, color, color, 1);
	gluPerspective(45, Constantes::LargoVentana / Constantes::AltoVentana, 0.1, 1000);
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
					barra.velocidadX = -1 * Constantes::VelocidadBarraX;
					if (!inicio) {
						inicio = true;
						bola.velocidadX = -1 * Constantes::VelocidadBolaX;
						bola.velocidadY = -1 * Constantes::VelocidadBolaY;
					}
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					barra.activo = true;
					barra.velocidadX = Constantes::VelocidadBarraX;
					if (!inicio) {
						inicio = true;
						bola.velocidadX = Constantes::VelocidadBolaX;
						bola.velocidadY = -1 * Constantes::VelocidadBolaY;
					}
				}
			}
			if (event.type == SDL_KEYUP) {
				barra.activo = false;
			}
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		tiempoActual = SDL_GetTicks();
		deltaTiempo = (tiempoActual - tiempoInicial) / 1000.0f;
		tiempoInicial = tiempoActual;

		barra.actualizar(deltaTiempo);
		barra.dibujar();

		bola.actualizar(deltaTiempo, Constantes::LargoVentana, Constantes::AltoVentana);
		bola.dibujar();

		enemigo1.actualizar(deltaTiempo);
		enemigo1.dibujar();

		enemigo2.actualizar(deltaTiempo);
		enemigo2.dibujar();

		enemigo3.actualizar(deltaTiempo);
		enemigo3.dibujar();

		if (inicio) {
			colisionBarraBola(bola, barra);
		}

		SDL_GL_SwapWindow(win);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
