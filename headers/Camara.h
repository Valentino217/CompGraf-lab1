#pragma once

#include "Barra.h" 

class Camara {
private:
    float eyeX, eyeY, eyeZ;       // Posición de la cámara
    float targetX, targetY, targetZ; // Punto al que mira
    float upX, upY, upZ;          // Vector "Hacia arriba" (normalmente 0, 1, 0)

    // --- Variables para la cámara en 3ra Persona (Órbita) ---
    float anguloHorizontal;
    float anguloVertical;
    float distanciaRadio;

    // --- Configuración de Proyección ---
    float fov;
    float aspectRatio;
    float zNear, zFar;

    // --- Estado ---
    int modoActual; 
public:
    Camara(float screenWidth, float screenHeight);

    // Cambiar el modo de visión
    void setModo(int modo);
    int getModo() const;
    void nextModo();
    // Actualiza la posición y el objetivo dependiendo del modo
    void actualizar(int mouseX, int mouseY, float barraX, float barraY);

    // Ejecuta las llamadas de OpenGL (glMatrixMode, gluPerspective, gluLookAt)
    void aplicar();
};