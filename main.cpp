#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include "../headers/Game.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	Game game;
	return game.Run();
}