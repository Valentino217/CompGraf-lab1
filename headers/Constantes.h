#pragma once

namespace Constantes
{
	// DIMENSIONES
	constexpr float LargoVentana = 640.0f;
	constexpr float AltoVentana = 480.0f;
	constexpr float BarraAlto = 10.0f;
	constexpr float BarraLargo = 100.0f;
	constexpr float BolaRadio = 10.0f;
	constexpr float EnemigoLargo = 40.0f;
	constexpr float EnemigoAlto = 40.0f;

	// POSICIONES
	constexpr float CentroVentanaX = LargoVentana / 2.0f;
	constexpr float BarraX = CentroVentanaX;
	constexpr float BarraY = 0.0f + BarraAlto;
	constexpr float BolaCentroX = CentroVentanaX;
	constexpr float BolaCentroY = BarraLargo + BolaRadio;
	constexpr float Enemigo1X = LargoVentana / 3.0f - EnemigoLargo / 2.0f;
	constexpr float Enemigo2X = LargoVentana / 2.0f - EnemigoLargo / 2.0f;
	constexpr float Enemigo3X = 2.0f * LargoVentana / 3.0f - EnemigoLargo / 2.0f;
	constexpr float Enemigo1Y = 2.0f * AltoVentana / 3.0f - EnemigoAlto / 2.0f;
	constexpr float Enemigo2Y = 1.75f * AltoVentana / 2.0f - EnemigoAlto / 2.0f;
	constexpr float Enemigo3Y = 2.0f * AltoVentana / 3.0f - EnemigoAlto / 2.0f;

	// VELOCIDADES
	constexpr float VelocidadBolaX = 150.0f;
	constexpr float VelocidadBolaY = 200.0f;
	constexpr float VelocidadBarraX = 400.0f;
	constexpr float VelocidadBarraY = 0.0f;
	constexpr float VelocidadEnemigo1X = 200.0f;
	constexpr float VelocidadEnemigo2X = 300.0f;
	constexpr float VelocidadBolaMinimaY = 50.0f;

	// DESPLAZAMIENTOS
	constexpr float BarraDX = LargoVentana - BarraLargo;
	constexpr float Enemigo1DX = 200.0f;
	constexpr float Enemigo2DX = 300.0f;
}
