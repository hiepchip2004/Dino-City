#include "CommonFunction.h"
#include "RenderWindow.h"
#include "Entity.h"

using namespace std;

#define WIDTH 1080
#define HEIGHT 756

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
		cout << "SDL Init failed.Error: " << SDL_GetError() << endl;
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		cout << "Failed PNG" << SDL_GetError() << endl;
	}
	RenderWindow window("Game v1.0", WIDTH, HEIGHT);

	SDL_Texture* grassTexture = window.loadTexture("Debug/image/Mon projet.png");

	vector<Entity> _entities = {Entity(0, 702, grassTexture),
								Entity(54, 702, grassTexture),
								Entity(108, 702, grassTexture),
								Entity(162, 702, grassTexture),
								Entity(216, 702, grassTexture),
								Entity(270, 702, grassTexture),
								Entity(324, 702, grassTexture),
								Entity(378, 702, grassTexture),
								Entity(432, 702, grassTexture),
								Entity(486, 702, grassTexture),
								Entity(540, 702, grassTexture),
								Entity(594, 702, grassTexture),
								Entity(648, 702, grassTexture),
								Entity(702, 702, grassTexture),
								Entity(756, 702, grassTexture),
								Entity(810, 702, grassTexture),
								Entity(864, 702, grassTexture),
								Entity(918, 702, grassTexture),
								Entity(972, 702, grassTexture),
								Entity(1026, 702, grassTexture),
									Entity(0, 0, grassTexture)};

	SDL_Event event;
	  
	bool buildSuccess = true;
	while (buildSuccess) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				buildSuccess = false;
			}
		}
		window.clear();
		for (Entity& e : _entities) {
			window.render(e);
		}

		window.display();
	}
	window.cleanUp();
	SDL_Quit();
	return 0;
}
