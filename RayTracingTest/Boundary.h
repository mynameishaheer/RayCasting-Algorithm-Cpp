#include <SDL.h>
#include "Vector.h"

class Boundary {

public:
	vector pointA;
	vector pointB;

	Boundary(int x1, int y1, int x2, int y2) {
		this->pointA.x = x1;
		this->pointA.y = y1;
		this->pointB.x = x2;
		this->pointB.y = y2;
		
	}

	void show(SDL_Renderer* renderer) {
		SDL_RenderDrawLine(renderer, this->pointA.x, this->pointA.y, this->pointB.x, this->pointB.y);
	}
};