#include<SDL.h>
#include<SDL_image.h>
#include<iostream>

#include "RenderWindow.h"
#include "Entity.h"

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 720;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
		cout << "SDL Init failed.Error: " << SDL_GetError() << endl;
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		cout << "Failed PNG" << SDL_GetError() << endl;
	}
	RenderWindow window("Tran Van Hiep", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("objects/4 Animated objects/Card.png");

	SDL_Event event;

	bool buildSuccess = true;
	while (buildSuccess) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				buildSuccess = false;
			}
		}
		window.clear();
		window.render(grassTexture);
		window.display();
	}
	window.cleanUp();

	SDL_Quit();
	return 0;
}
