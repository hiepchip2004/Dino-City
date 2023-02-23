#include<SDL.h>
#include<SDL_image.h>
#include "RenderWindow.h"

#include<iostream>
using namespace std;

RenderWindow::RenderWindow(const char* title, int WIDTH, int HEIGHT)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Window fail. CAN NOT OPEN!" << SDL_GetError() << endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
SDL_Texture* RenderWindow::loadTexture(const char* fPath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, fPath);
	if (texture == NULL)
	{
		cout << "Could not load Image. Error: " << SDL_GetError() << endl;
	}
	return texture;
}
void RenderWindow::cleanUp() 
{
	SDL_DestroyWindow(window);
}
void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}
void RenderWindow::render(SDL_Texture* tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	SDL_Rect dst;
	dst.x = 100;
	dst.y = 200;
	dst.w = 32 ;
	dst.h = 32 ;
	SDL_RenderCopy(renderer, tex, &src, &dst);
}
void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
