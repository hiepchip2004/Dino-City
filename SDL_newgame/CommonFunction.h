#ifndef COMMON_FUNCT_H
#define COMMON_FUNCT_H

#include <vector>
#include <iostream>
#include <string>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;
	
typedef SDL_Rect Rect;
typedef SDL_Color Color;
const int WIDTH = 1080;
const int HEIGHT = 756;

// define commonly used functions
void logSDLError(ostream& os, const string& msg);
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

#endif