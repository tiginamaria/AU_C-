#include "figure.h"

Figure::Figure(int id, int x, int y) {
	this->id = id;
	this->x = x;
	this->y = y;
}

int Figure::getX() const {
	return x;
}

int Figure::getY() const {
	return y;
}

int Figure::getId() const {
	return id;
}

void Figure::move(int new_x, int new_y) {
    this->x = new_x;
    this->y = new_y;
}

Figure::~Figure(){}

