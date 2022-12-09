#include <SDL.h>
#include <cmath>
#include "Vector.h"

class Ray {
public:

	vector position;
	vector direction;
	vector* pt = new vector();

	Ray(int x, int y, float angle) {
		this->position.x = x;
		this->position.y = y;
		this->direction.x = cos(angle);
		this->direction.y = sin(angle);
	}

	void show(SDL_Renderer* renderer) {

		//this is basically acting the same way translate() works in JS
		//it is changing the origin of the line to the x,y passed in as arguments 
		//then it uses the direction vectors to calculate the angle of the ray
		SDL_RenderDrawLine(renderer, this->position.x, this->position.y,
			(this->position.x + (this->direction.x)),
			(this->position.y + (this->direction.y)));

	};

	void update(int x, int y) {
		this->position.x += x;
		this->position.y += y;
	
	}

	void CW90() {
		float tempX = this->direction.x;

		this->direction.x = -1 * this->direction.y;
		this->direction.y = tempX;
	}
	void ACW90() {
		float tempX = this->direction.x;

		this->direction.x = this->direction.y;
		this->direction.y = -1 * tempX;
	}
	void CW270() {
		float tempX = this->direction.x;
		
		this->direction.x = this->direction.y;
		this->direction.y - -1 * tempX;
	}
	void ACW270() {
		float tempX = this->direction.x;

		this->direction.x = -1 * this->direction.y;
		this->direction.y = tempX;
	}
	void ACW180_CW180() {
		float tempX = this->direction.x;

		this->direction.x = -1 * this->direction.x;
		this->direction.y = -1 * this->direction.y;
	}

	vector* cast(Boundary* wall) {
		//the starting and ending points on the wall
		float x1 = wall->pointA.x;
		float y1 = wall->pointA.y;
		float x2 = wall->pointB.x;
		float y2 = wall->pointB.y;

		//the starting and the ending point of the ray
		float x3 = this->position.x;
		float y3 = this->position.y;
		float x4 = this->position.x + this->direction.x;
		float y4 = this->position.y + this->direction.y;

		float den = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));

		//if lines are parallel return false
		if (den == 0) {
			return nullptr;
		}

		float t = (((x1 - x3) * (y3 - y4)) - ((y1 - y3) * (x3 - x4))) / den;

		float u = -1 * ((((x1 - x2) * (y1 - y3)) - ((y1 - y2) * (x1 - x3))) / den);


		if (t > 0 && t < 1 && u>0) {
			
			float ptX = x1 + t * (x2 - x1);
			float ptY = y1 + t * (y2 - y1);

			pt->x = ptX;
			pt->y = ptY;

			return pt;
		}
		else {
			return  nullptr;
		}


	};

};