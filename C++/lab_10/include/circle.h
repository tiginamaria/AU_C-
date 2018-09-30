#pragma once

#include "figure.h"

class Circle : public Figure {
  public:
    Circle(int id, int x, int y, int radius, const char* label);
    virtual void print() const;
    virtual bool is_inside(int x, int y) const;
    bool in(int x, int x0, int len) const;
    virtual void zoom(int factor);
    virtual ~Circle();
    
  private:
  	int r;
  	char* _label;
};
