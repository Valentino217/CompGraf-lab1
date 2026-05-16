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
    anguloHorizontal = 0.0f;     // 0 = Justo detrás de la barra
    anguloVertical = 1.107f;     // Elevación (arctan(300/150) en radianes)
    distanciaRadio = 335.41f;    // Hipotenusa exacta de 150 y 300
    
    setModo(0); // Empezar en cenital
}

void Camara::nextModo(){
    if (modoActual == 2) {
        modoActual = 0;
		fov = 45.0f;
        upX = 0.0f; upY = 1.0f; upZ = 0.0f;
    } else {
        modoActual++;
        fov = 60.0f;
        upX = 0.0f; upY = 0.0f; upZ = 1.0f;
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
        // --- MODO CENITAL ---
        eyeX = 320.0f; eyeY = 240.0f; eyeZ = 600.0f;
        targetX = 320.0f; targetY = 240.0f; targetZ = 0.0f;
    } 
    else if (modoActual == 1) {
        // --- MODO TERCERA PERSONA  ---
        targetX = barraX;
        targetY = barraY;
        targetZ = 0.0f;

        // Acumular el movimiento del mouse
        anguloHorizontal += static_cast<float>(mouseX) * 0.003f;
        anguloVertical += static_cast<float>(mouseY) * 0.003f;

        if (anguloVertical < 0.1f) anguloVertical = 0.1f;
        if (anguloVertical > 1.5f) anguloVertical = 1.5f;

        if (anguloHorizontal < -1.57f) anguloHorizontal = -1.57f;
        if (anguloHorizontal > 1.57f)  anguloHorizontal = 1.57f;

        float radioXY = distanciaRadio * cos(anguloVertical);

        eyeX = targetX + radioXY * sin(anguloHorizontal);
        eyeY = targetY - radioXY * cos(anguloHorizontal); 
        eyeZ = targetZ + distanciaRadio * sin(anguloVertical);
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