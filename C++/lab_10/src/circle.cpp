#include "circle.h"
#include <stdio.h>
#include <string.h>
#include <algorithm>

Circle::Circle(int id, int x, int y, int radius, const char* label):Figure(id, x, y), r(radius) {
	_label = new char[strlen(label) + 1];
	strcpy(_label, label);
}

void Circle::print() const {
	printf("Circle %d: x = %d y = %d radius = %d label = %s\n", getId(), getX(), getY(), r, _label);
}

bool Circle::in(int x, int x0, int len) const {
	return (2 * abs(x - x0) <= len);
}

bool Circle::is_inside(int x, int y) const {
	return in(getX(), x, r) && in(getY(), y, r);
}

void Circle::zoom(int factor) {
	r = r * factor;
}

Circle::~Circle() {
	delete [] _label;
}
