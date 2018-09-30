#include "scheme.h"

const int NOT_FOUND = -1;

Scheme::Scheme(int capacity) {
	_figures = new Figure* [capacity];
	fg_count = 0;
}

int Scheme::find_figure(int id) {
	for (int i = 0; i < fg_count; i++)
		if (_figures[i]->getId() == id)
			return i;
	return NOT_FOUND;
}

void Scheme::push_back_figure(Figure* fg) {
	_figures[fg_count] = fg;
	fg_count++;
}

void Scheme::copy_front(int to_del) {
	for (int i = to_del; i < fg_count - 1; i ++)
		_figures[i] = _figures[i + 1];
	fg_count--;
}

void Scheme::remove_figure(int id) {
	int to_del = find_figure(id);
	if (to_del != NOT_FOUND) {
		delete _figures[to_del];
		copy_front(to_del);
	}
}

void Scheme::print_all_figures() {
	for (int i = 0; i < fg_count; i++)
		_figures[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
	int to_zoom = find_figure(id);
	if (to_zoom != NOT_FOUND) {
		_figures[to_zoom]->zoom(factor);
	}
}

Figure* Scheme::is_inside_figure(int x, int y) {
	for (int i = 0; i < fg_count; i++)
		if (_figures[i]->is_inside(x, y))
				return _figures[i];
	return 0;
}

void Scheme::move(int id, int new_x, int new_y) {
	int to_move = find_figure(id);
	if (to_move != NOT_FOUND) {
		_figures[to_move]->move(new_x, new_y);
	}
}

Scheme::~Scheme() {
	for (int i = 0; i < fg_count; i ++)
		delete _figures[i];
	delete [] _figures;
}






