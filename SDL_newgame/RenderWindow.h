#pragma once

#include "CommonFunction.h"
#include "Entity.h"

class RenderWindow {
public:
	RenderWindow(const char* title, int WIDTH, int HEIGHT);
	SDL_Texture* loadTexture(const char* fPath);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* tex;
};
