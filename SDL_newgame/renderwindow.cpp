#include "CommonFunction.h"
#include "RenderWindow.h"
#include "Entity.h"

using namespace std;

RenderWindow::RenderWindow(const char* title, int WIDTH, int HEIGHT)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) 
	{
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
void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst; 
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w / 20;
	dst.h = p_entity.getCurrentFrame().h / 20;
	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}
void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
	