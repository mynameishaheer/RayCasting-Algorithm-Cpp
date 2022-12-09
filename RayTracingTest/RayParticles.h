#pragma once
#include "Ray.h"
#include <SDL.h>
#include <cmath>
#include<limits>

using namespace std;

const int NUMRAYS = 220;

class RayParticle {
public:
	vector position;
	int currentDirection = 0; //0->TOP, 1->RIGHT, 2->LEFT 3->BOTTOM
	Ray* rays[NUMRAYS];
	float INF = numeric_limits<float>::infinity();
	SDL_Rect* visible = new SDL_Rect();


	RayParticle(int x, int y) {
		this->position.x = x;
		this->position.y = y;

		int index = 0;
		for (int i = 245; i < 300; i += 1) {
			rays[index] = new Ray(this->position.x, this->position.y, (i * (3.14159265359 / 180)));
			index++;
			rays[index] = new Ray(this->position.x + 0.25, this->position.y + 0.25, ((i + 0.25) * (3.14159265359 / 180)));
			index++;
			rays[index] = new Ray(this->position.x + 0.5, this->position.y + 0.5, ((i + 0.5) * (3.14159265359 / 180)));
			index++;
			rays[index] = new Ray(this->position.x + 0.75, this->position.y + 0.75, ((i + 0.75) * (3.14159265359 / 180)));
			index++;
		}
	}

	void show(SDL_Renderer* renderer) {

		for (int i = 0; i < NUMRAYS; i++) {
			rays[i]->show(renderer);
		}
	}

	void update(int x, int y) {
		this->position.x += x;
		this->position.y += y;
		for (int i = 0; i < NUMRAYS; i++) {
			rays[i]->update(x, y);

		}
	}

	void changeDirection(int direction) {
		if (currentDirection != direction) {
			switch (currentDirection)
			{
				//if my curent direction is UP
			case 0:
				//and if I press RIGHT
				if (direction == 1) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees clockwise
						rays[i]->CW90();
					}
					currentDirection = direction;
				}
				//and if I press LEFT
				if (direction == 2) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees anti-clockwise
						rays[i]->ACW90();
					}
					currentDirection = direction;
				}
				//and if I press DOWN
				if (direction == 3) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 180 degrees
						rays[i]->ACW180_CW180();
					}
					currentDirection = direction;
				}
				break;

				//if my curent direction is RIGHT
			case 1:
				//and if I press UP
				if (direction == 0) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees anti-clockwise
						rays[i]->ACW90();
					}
					currentDirection = direction;
				}
				//and if I press LEFT
				if (direction == 2) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 180 degrees
						rays[i]->ACW180_CW180();
					}
					currentDirection = direction;
				}
				//and if I press DOWN
				if (direction == 3) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees clockwise
						rays[i]->CW90();
					}
					currentDirection = direction;
				}
				break;

				//if my curent direction is LEFT
			case 2:
				//and if I press UP
				if (direction == 0) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees clockwise
						rays[i]->CW90();
					}
					currentDirection = direction;
				}
				//and if I press RIGHT
				if (direction == 1) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 180 degrees
						rays[i]->ACW180_CW180();
					}
					currentDirection = direction;
				}
				//and if I press DOWN
				if (direction == 3) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees anti-clockwise
						rays[i]->ACW90();
					}
					currentDirection = direction;
				}
				break;

				//if my curent direction is DOWN
			case 3:
				//and if I press UP
				if (direction == 0) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 180 degrees
						rays[i]->ACW180_CW180();
					}
					currentDirection = direction;
				}
				//and if I press RIGHT
				if (direction == 1) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees anti-clockwise
						rays[i]->ACW90();
					}
					currentDirection = direction;
				}
				//and if I press LEFT
				if (direction == 2) {
					for (int i = 0; i < NUMRAYS; i++) {
						//rotate me 90 degrees clockwise
						rays[i]->CW90();
					}
					currentDirection = direction;
				}
				break;
			default:
				break;
			}
		}
		//rays[i]->changeDirection();

	}

	float distance(int x1, int y1, float x2, float y2) {
		int a = (int)x2 - x1;
		int b = (int)y2 - y1;
		int asq = a * a;
		int bsq = b * b;
		int sum = asq + bsq;
		int sqr = (int)(sqrt(sum));

		return sqr;

	}


	void look(Boundary** walls, SDL_Renderer* renderer) {
		for (int i = 0; i < NUMRAYS; i++) {
			float closestPointX = NULL;
			float closestPointY = NULL;
			float record = INF;
			for (int j = 0; j < 9; j++) {
				vector* pt;
				pt = rays[i]->cast(*(walls + j));
				if (pt != nullptr) {
					float distance = this->distance(this->position.x, this->position.y, pt->x, pt->y);
					if (distance < record) {
						record = distance;
						closestPointX = pt->x;
						closestPointY = pt->y;
					}
				}
			}
			if (closestPointX != NULL) {

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 55);
				//these are the rays that intersect the wall
				SDL_RenderDrawLine(renderer, this->position.x, this->position.y, closestPointX, closestPointY);

				visible->x = closestPointX;
				visible->y = closestPointY;
				visible->w = 2;
				visible->h = 2;

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawRect(renderer, visible);
				SDL_RenderFillRect(renderer, visible);
			}
		}
	}
};
