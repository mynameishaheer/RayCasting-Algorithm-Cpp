#include <SDL.h>
#include "Vector.h"

class Boundary {

public:
	vector pointA;
	vector pointB;
	//float x1, y1, x2, y2;

	Boundary(int x1, int y1, int x2, int y2) {
		this->pointA.x = x1;
		this->pointA.y = y1;
		this->pointB.x = x2;
		this->pointB.y = y2;
		
		
		//this->x1 = x1;
		//this->y1 = y1;
		//this->x2 = x2;
		//this->y2 = y2;
	}

	void show(SDL_Renderer* renderer) {
		SDL_RenderDrawLine(renderer, this->pointA.x, this->pointA.y, this->pointB.x, this->pointB.y);
		//SDL_RenderDrawLine(renderer, this->x1, this->y1, this->x2, this->y2);
	}
};