#include "background.h"

Background::Background(SDL_Renderer* renderer) {
	m_renderer = renderer;
	SDL_Surface* surface = IMG_Load("Debug/image/background.png");
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	SDL_FreeSurface(surface);
}

void Background::render() {
	SDL_Rect desRect = { 0, 0, WIDTH, HEIGHT};
	SDL_RenderCopy(m_renderer, m_texture, NULL, &desRect);
}

Background::~Background() {
	SDL_DestroyTexture(m_texture);
}