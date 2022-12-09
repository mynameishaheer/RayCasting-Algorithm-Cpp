#include <SDL.h>
#include <iostream>
#include "Boundary.h"
#include "RayParticles.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

const int MOVE = 5;


int main(int argc, char* argv[])
{

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create the window
	SDL_Window* window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window)
	{
		std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}


	// Create the renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


	bool quit = false;

	SDL_Event e;
	int mouseX = 1;
	int mouseY = 1;

	Boundary* walls[9];

	int s = 5;
	//left boundary
	walls[0] = new Boundary(s, s, s, SCREEN_HEIGHT);
	//top boundary
	walls[1] = new Boundary(s, s, SCREEN_WIDTH, s);
	//right boundary
	walls[2] = new Boundary(SCREEN_WIDTH - s, s, SCREEN_WIDTH, SCREEN_HEIGHT);
	//bottom boundary 
	walls[3] = new Boundary(s, SCREEN_HEIGHT - s, SCREEN_WIDTH - s, SCREEN_HEIGHT - s);

	for (int i = 4; i < 9; i++) {
		int x1 = rand() % SCREEN_WIDTH;
		int x2 = rand() % SCREEN_WIDTH;
		int y1 = rand() % SCREEN_HEIGHT;
		int y2 = rand() % SCREEN_HEIGHT;

		walls[i] = new Boundary(x1, y1, x2, y2);
	}

	RayParticle* particle = new RayParticle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	while (!quit) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			if (e.type == SDL_KEYDOWN) {
				if (SDLK_ESCAPE == e.key.keysym.sym) {
					quit = true;
					break;
				}
				//UP
				if (SDLK_UP == e.key.keysym.sym) {
					particle->update(0, -MOVE);
					particle->changeDirection(0);
				}
				//RIGHT
				if (SDLK_RIGHT == e.key.keysym.sym) {
					particle->update(MOVE, 0);
					particle->changeDirection(1);
				}
				//LEFT
				if (SDLK_LEFT == e.key.keysym.sym) {
					particle->update(-MOVE, 0);
					particle->changeDirection(2);
				}
				//DOWN
				if (SDLK_DOWN == e.key.keysym.sym) {
					particle->update(0, MOVE);
					particle->changeDirection(3);
				}
			}

			//store mouse coordinates
			if (e.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&mouseX, &mouseY);
			}
		}

		// Set the background color to BLACK
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Set the wall color to WHITE
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 25);

		//draw the wall
		for (int i = 0; i < 9; i++) {
			walls[i]->show(renderer);
		}
		Boundary** ptr = walls;

		particle->show(renderer);
		particle->look(ptr, renderer);

		//show the screen
		SDL_RenderPresent(renderer);

	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}