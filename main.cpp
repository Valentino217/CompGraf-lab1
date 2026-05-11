#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

using namespace std;

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
float centroVentanaX = largoVentana / 2;
float barraX = centroVentanaX - barraLargo / 2;
float barraY = altoVentana - barraAlto;
float bolaCentroX = centroVentanaX;
float bolaCentroY = altoVentana - barraAlto - bolaRadio;
float enemigo1X = largoVentana / 3 - enemigoLargo / 2;
float enemigo2X = largoVentana / 2 - enemigoLargo / 2;
float enemigo3X = 2 * largoVentana / 3 - enemigoLargo / 2;
float enemigo1Y = altoVentana / 3 - enemigoAlto / 2;
float enemigo2Y = altoVentana / 2 - enemigoAlto / 2;
float enemigo3Y = altoVentana / 3 - enemigoAlto / 2;

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
	float largo, alto;
	float posicionIzq, posicionSup;
	float velocidadX, velocidadY;
	bool activo;
	float desplazamientoXMax;
	float limiteIzq, limiteDer;

	Rect(float l, float a, float x, float y, float vx, float vy, bool act, float dx) {
		largo = l;
		alto = a;
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
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex2f(posicionIzq, posicionSup);
		glVertex2f(posicionIzq + largo, posicionSup);
		glVertex2f(posicionIzq + largo, posicionSup + alto);
		glVertex2f(posicionIzq, posicionSup + alto);
		glEnd();
	}
};

class Enemigo : public Rect {
public :
	Enemigo(float l, float a, float x, float y, float vx, float vy, bool act, float dx) : Rect(l, a, x, y, vx, vy, act, dx) {};

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
public :
	Barra(float l, float a, float x, float y, float vx, float vy, bool act, float dx) : Rect(l, a, x, y, vx, vy, act, dx) {};

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

void colisionBarraBola(Bola& bola, Barra& barra) {
	if (bola.centroX + bola.radio >= barra.posicionIzq && bola.centroX - bola.radio <= barra.posicionIzq + barra.largo) {
		if (bola.centroY + bola.radio >= barra.posicionSup && bola.centroY - bola.radio <= barra.posicionSup + barra.alto) {
			bola.velocidadY = -1 * bola.velocidadY;
			if (barra.velocidadX * bola.velocidadX < 0) {
				bola.velocidadX = -1 * bola.velocidadX;
			}
		}
	}
	return;
}

int main(int argc, char *argv[]) {

	Bola bola(bolaCentroX, bolaCentroY, 0, 0, bolaRadio);
	Barra barra(barraLargo, barraAlto, barraX, barraY, velocidadBarraX, velocidadBarraY, false, barraDX);
	Enemigo enemigo1(enemigoLargo, enemigoAlto, enemigo1X, enemigo1Y, velocidadEnemigo1X, 0, true, enemigo1DX);
	Enemigo enemigo2(enemigoLargo, enemigoAlto, enemigo2X, enemigo2Y, velocidadEnemigo2X, 0, true, enemigo2DX);
	Enemigo enemigo3(enemigoLargo, enemigoAlto, enemigo3X, enemigo3Y, velocidadEnemigo1X, 0, true, enemigo1DX);

	//VELOCIDADES DE OBJETOS
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
	glLoadIdentity();

	float color = 0;
	glClearColor(color, color, color, 1);

	gluOrtho2D(0, 640, 480, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	bool arkanoid = true;
	SDL_Event event;
	Uint32 tiempoInicial = SDL_GetTicks();
	Uint32 tiempoActual = tiempoInicial;
	float deltaTiempo = 0.0f;

	while (arkanoid) {
		
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

		glClearColor(color, color, color, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		
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

		if (inicio) {
			colisionBarraBola(bola, barra);
		}
		
		SDL_GL_SwapWindow(win);
	}

	return 0;
}

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