#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "CommonFunction.h"
#include "SDL_image.h"

class Background {
public:
	Background(SDL_Renderer* renderer);
	void render();
	~Background();

private:
	SDL_Texture* m_texture;
	SDL_Renderer* m_renderer;

};

#endif 