#pragma once
#include "Ray.h"
#include <SDL.h>
#include <cmath>
#include<limits>

using namespace std;

const int NUMRAYS = 3;

class RayParticle {
public:
	vector position;

	//int posX;
	//int posY;
	Ray* rays[NUMRAYS];
	float INF = numeric_limits<float>::infinity();


	RayParticle(int x, int y) {
		this->position.x = x;
		this->position.y = y;

		int index = 0;
		for (int i = 240; i < 300; i += 20) {
			rays[index] = new Ray(this->position.x, this->position.y, (i * (3.14159265359 / 180)));
			index++;
		}
	}


	//RayParticle(int x, int y) {
	//	this->posX = x;
	//	this->posY = y;

	//	//printf("%d\n%d\n", this->posX, this->posY);
	//	int index = 0;
	//	for (int i = 240; i < 300; i += 20) {
	//		rays[index] = new Ray(this->posX, this->posY, (i * (3.14159265359 / 180)));
	//		index++;
	//		//printf("Index: %d\n Angle:%f\n", (i/10), (i * (3.14159265359 / 180)));
	//		//printf("X:%f\nY:%f\n\n", cos((i * (3.14159265359 / 180))), sin((i * (3.14159265359 / 180))));

	//	}
	//}

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

	//void update(int x, int y) {
	//	this->posX += x;
	//	this->posY += y;
	//	for (int i = 0; i < NUMRAYS; i++) {
	//		//rays[i]->lookAt(x, y);
	//		rays[i]->update(x, y);

	//	}
	//}

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

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				//these are the rays that intersect the wall
				SDL_RenderDrawLine(renderer, this->position.x, this->position.y, closestPointX, closestPointY);
			}
		}
	}

	//void look(Boundary** walls, SDL_Renderer* renderer) {
	//	for (int i = 0; i < NUMRAYS; i++) {
	//		float closestPointX = NULL;
	//		float closestPointY = NULL;
	//		float record = INF;
	//		for (int j = 0; j < 9; j++) {
	//			vector* pt;
	//			pt = rays[i]->cast(*(walls + j));
	//			if (pt != nullptr) {
	//				float distance = this->distance(this->posX, this->posY, pt->x, pt->y);
	//				if (distance < record) {
	//					record = distance;
	//					closestPointX = pt->x;
	//					closestPointY = pt->y;
	//				}
	//			}
	//		}
	//		if (closestPointX != NULL) {

	//			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//			//these are the rays that intersect the wall
	//			SDL_RenderDrawLine(renderer, this->posX, this->posY, closestPointX, closestPointY);
	//		}
	//	}
	//}

	//void look(Boundary* wall, SDL_Renderer* renderer) {
	//	for (int i = 0; i < 18; i++) {

	//		vector * pt;
	//		pt = rays[i]->cast(wall);
	//		if (pt != nullptr ) {
	//			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//			//these are the rays that intersect the wall
	//			//SDL_RenderDrawLine(renderer, this->posX, this->posY, *(pt + 0), *(pt + 1));

	//			std::cout << "Particle ptX: " << pt->x << std::endl;
	//			std::cout << "Particle ptY: " << pt->y << std::endl;
	//			//std::cout << "Particle ptY: " << *(pt + 1) << std::endl;

	//		}
	//	}
	//}
};
