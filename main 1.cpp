#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

using namespace std;

void dibujarCubo(float s) {

	glBegin(GL_QUADS);
	// Cara Frontal
	glColor3f(1.0f, 0.0f, 0.0f);
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
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-s, s, -s);
	glVertex3f(-s, s, s);
	glVertex3f(s, s, s);
	glVertex3f(s, s, -s);

	// Cara Inferior
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-s, -s, -s);
	glVertex3f(s, -s, -s);
	glVertex3f(s, -s, s);
	glVertex3f(-s, -s, s);

	// Cara Derecha
	glColor3f(1.0f, 1.0f, 1.0f);
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

int main(int argc, char *argv[]) {
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO)<0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

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

	//TEXTURA
	char* archivo2 = new char[20];
	archivo2 = "../pelota2.png";

	//Cargar Imagen 2
	FREE_IMAGE_FORMAT FIF2 = FreeImage_GetFIFFromFilename(archivo2);
	FIBITMAP* bitmap2 = FreeImage_Load(FIF2, archivo2);
	bitmap2 = FreeImage_ConvertTo24Bits(bitmap2);
	int w2 = FreeImage_GetWidth(bitmap2);
	int h2 = FreeImage_GetHeight(bitmap2);
	void* datos2 = FreeImage_GetBits(bitmap2);

	GLuint textura2;
	glGenTextures(1, &textura2);
	glBindTexture(GL_TEXTURE_2D, textura2);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w2, h2, 0, GL_BGR, GL_UNSIGNED_BYTE, datos2);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//FIN TEXTURA


	bool fin = false;
	bool rotate = false;
	int cambio = 0;
	int mouse1, mouse2;

	SDL_Event evento;

	float x, y, z, x1, x2, x3, x4;

	
	x = 0;
	y = 0;
	z = 7;
	x1 = 0;
	x2 = 0;
	x3 = 0;
	x4 = 0;
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
		gluLookAt(x, y, z, x1, x2, x3, x4, 1, 0);


		switch (cambio) {
		case 0:
			x = 0;
			y = 0;
			z = 7;
			x3 = 0;
			x4 = 0;
			break;
		case 1:
			x = 0;
			y = -6;
			z = 3;
			break;
		case 2:
			x1 = (mouse1 - 320) / 100.f;
			x2 = -(mouse2 - 240)/ 100.f;

			break;
		}
		//PRENDO LA LUZ (SIEMPRE DESPUES DEL gluLookAt)
		/*		glEnable(GL_LIGHT0); // habilita la luz 0
		glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, colorLuz);
		
		glEnable(GL_LIGHT1); // habilita la luz 1
		glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, colorLuz);
		*/

		//Cancha
		glPushMatrix();
		glScalef(1.75, 1.75, 1);
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(1.5, 2.0, -2.0);
		glVertex3f(1.5, -2.0, -2.0);
		glVertex3f(-1.5, -2.0, -2.0);
		glVertex3f(-1.5, 2.0, -2.0);
		glEnd();
		glPopMatrix();


		//TRANSFORMACIONES LINEALES
		if (rotate){
			degrees = degrees + 1;
		}
		//DIBUJAR OBJETOS
		//DIBUJO TRIANGULO CON TEXTURA
		/*
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
		glPopMatrix();
		*/

		//DIBUJO JUGADOR
		glPushMatrix();
		glTranslatef(0, -2.5, -.5);
		glRotatef(degrees * 1, 0.0, 1.0, 0.0);
		glScalef(.5, .5,.5);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		dibujarCubo(1);
		glPopMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Dibujo de defensores
		for (int i = -2; i <= 2; i++) {
			glPushMatrix();
			// 1. Traslación: 
			// Eje X: 'i * 1.2f' los separa horizontalmente.
			// Eje Y: '3.0f' los coloca en la parte superior de la cancha.
			// Eje Z: '-0.5f' los mantiene a la misma profundidad que el cubo original.
			glTranslatef(i * 1.2f, 2.5f, -0.5f);
			// 2. Rotación (Opcional): Los hacemos rotar usando tu variable 'degrees'
			glRotatef(degrees * 2, 0.0, 1.0, 0.0);
			// 3. Escala: Los hacemos mucho más pequeños (ej. 0.2)
			glScalef(0.2f, 0.2f, 0.2f);
			// 4. Dibujar el cubo
			dibujarCubo(1);
			glPopMatrix();
		}

		//Pelota
		glPushMatrix();
		glTranslatef(0, 0, -1.0); 
		glRotatef(degrees, 1, 1, 0);
		GLUquadric* q = gluNewQuadric();
		gluQuadricTexture(q, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textura2);
		gluSphere(q, 0.3, 8, 8);
		glDisable(GL_TEXTURE_2D);
		gluDeleteQuadric(q);
		glPopMatrix();


		//DIBUJO TRIANGULO CON LUZ
		/*
		glEnable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
			glNormal3f(0, 0, 1);
			glVertex3f(-1., -1., 0.);
			glVertex3f(-3., -1., 0.);
			glVertex3f(-2., 1., 0.);
		glEnd();
		glDisable(GL_LIGHTING);
		*/

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
				case SDLK_v:
					if (cambio != 2)
						cambio++;
					else
						cambio = 0;
					break;
				}
				break;
			case SDL_KEYDOWN:
				switch (evento.key.keysym.sym) {
				case SDLK_w:
					if (cambio == 2)
						y = y + 0.1;
					break;
				case SDLK_a:
					if (cambio == 2)
						x = x - 0.1;
					break;
				case SDLK_s:
					if (cambio == 2)
						y = y - 0.1;
					break;
				case SDLK_d:
					if (cambio == 2)
						x = x + 0.1;
					break;
				case SDLK_SPACE:
					if (cambio == 2)
						z = z + 0.1;
					break;
				case SDLK_z:
					if (cambio == 2)
						z = z - 0.1;
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse1, &mouse2);
				break;
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
	return 0;
}
