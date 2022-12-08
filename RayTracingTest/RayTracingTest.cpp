#include <SDL.h>
#include <iostream>
#include "Boundary.h"
#include "RayParticles.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
	walls[3] = new Boundary(s, SCREEN_HEIGHT -s, SCREEN_WIDTH -s, SCREEN_HEIGHT -s);

	for (int i = 4; i < 9; i++) {
		int x1 = rand() % SCREEN_WIDTH;
		int x2 = rand() % SCREEN_WIDTH;
		int y1 = rand() % SCREEN_HEIGHT;
		int y2 = rand() % SCREEN_HEIGHT;

		walls[i] = new Boundary(x1, y1, x2, y2);
	}

	//Boundary* wall = new Boundary(100, 100, 200, 300);
	//Ray* ray = new Ray(100, 200);
	RayParticle* particle = new RayParticle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	//SDL_Rect* rect = new SDL_Rect();

	while (!quit) {

		//store mouse coordinates
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
				if (SDLK_UP == e.key.keysym.sym) {
					particle->update(0, -MOVE);
				}
				if (SDLK_DOWN== e.key.keysym.sym) {
					particle->update(0, MOVE);
				}
				if (SDLK_LEFT == e.key.keysym.sym) {
					particle->update( -MOVE, 0);
				}
				if (SDLK_RIGHT == e.key.keysym.sym) {
					particle->update(MOVE, 0);
				}
			}

			if (e.type == SDL_MOUSEMOTION) {
				SDL_GetMouseState(&mouseX, &mouseY);
			}
		}

		// Set the background color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		// Set the ray color to black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		//draw the wall
		for (int i = 0; i < 9; i++) {
			walls[i]->show(renderer);
		}
		Boundary** ptr = walls;
		//wall->show(renderer);

		//particle->update(mouseX, mouseY);
		particle->show(renderer);
		particle->look(ptr, renderer);
		//particle->look(wall, renderer);

		////determine the direction of the ray
		//ray->lookAt(mouseX, mouseY);
		////calculate if the ray is hitting the wall
		//float* pt;
		//pt = ray->cast(wall);
		////draw the ray
		//ray->show(renderer);

		//if (pt != nullptr) {
		//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);


		//	//SDL_RenderFillRect(renderer, rect);
		//	rect->x = *(pt + 0);
		//	rect->y = *(pt + 1);
		//	rect->w = 1;
		//	rect->h = 20;

		//	SDL_RenderDrawRect(renderer, rect);

		//	//SDL_RenderDrawPoint(renderer, *(pt + 0), *(pt + 1));
		//}


		//show the screen
		SDL_RenderPresent(renderer);

		// Wait for 5 seconds
		//SDL_Delay(50);

	}

	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}