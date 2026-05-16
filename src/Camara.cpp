#include "../headers/Camara.h"

#include "SDL.h"
#include "SDL_opengl.h"

#include <GL/glu.h>
#include <iostream>

Camara::Camara(float screenWidth, float screenHeight) {
    aspectRatio = screenWidth / screenHeight;
    zNear = 0.1f;
    zFar = 1000.0f;
    
    upX = 0.0f; upY = 1.0f; upZ = 0.0f;
    
    // Valores iniciales para 3ra persona
    anguloHorizontal = 0.0f;
    anguloVertical = 0.5f;
    distanciaRadio = 250.0f;
    
    setModo(0); // Empezar en cenital
}

void Camara::nextModo(){
    if (modoActual == 2) {
        modoActual = 0;
		fov = 45.0f;
    } else {
        modoActual++;
        fov = 60.0f;
	}
}

void Camara::setModo(int modo) {
    modoActual = modo;
    if (modoActual == 0) {
        fov = 45.0f; // FOV estándar para vista plana
    } else if (modoActual == 1) {
        fov = 60.0f; // FOV más amplio para 3ra persona
    }
}

int Camara::getModo() const {
    return modoActual;
}

void Camara::actualizar(int mouseX, int mouseY, float barraX, float barraY) {
    if (modoActual == 0) {
        // --- MODO CENITAL (Fija mirando al centro) ---
        eyeX = 320.0f; eyeY = 240.0f; eyeZ = 600.0f;
        targetX = 320.0f; targetY = 240.0f; targetZ = 0.0f;
    } 
    else if (modoActual == 1) {
        // --- MODO TERCERA PERSONA (Sigue a la barra) ---
        // El objetivo es la barra
		eyeZ = 200.0f;
        targetX = barraX;
        targetY = barraY +50;
        targetZ = 0.0f;

        float deltaX = static_cast<float>(mouseX) - 320;
        float deltaY = static_cast<float>(mouseY) - 240;
        eyeX = barraX - deltaX;
        eyeY = barraY - 150.0f - deltaY;
    }
}

void Camara::aplicar() {
    // 1. Aplicar la perspectiva (FOV)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, aspectRatio, zNear, zFar);

    // 2. Aplicar la posición de la cámara (LookAt)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);
}