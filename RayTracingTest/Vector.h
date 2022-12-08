#pragma once

class vector {
public:
	float x;
	float y;

	vector() {
		this->x = 0;
		this->y = 0;
	}

	vector(float _x, float _y) {
		this->x = _x;
		this->y = _y;

	}

	void normalize() {
		float magnitude = sqrt((this->x* this->y) + (this->y* this->x));
		this->x = (this->x / magnitude);
		this->y = (this->y / magnitude);
	}
};