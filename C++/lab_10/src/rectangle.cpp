#include "rectangle.h"
#include <stdio.h>
#include <algorithm>

Rectangle::Rectangle(int id, int x, int y, int width, int height):Figure(id, x, y), w(width), h(height){}

void Rectangle::print() const {
	printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", getId(), getX(), getY(), w, h);
}

bool Rectangle::in(int x, int x0, int len) const {
	return (2 * abs(x - x0) <= len);
}

bool Rectangle::is_inside(int x, int y) const {
	return in(getX(), x, w) && in(getY(), y, h);
}

void Rectangle::zoom(int factor) {
	w = w * factor;
	h = h * factor;
}

Rectangle::~Rectangle(){}
