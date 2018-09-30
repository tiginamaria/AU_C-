#include "figure.h"

class Rectangle : public Figure {
  public:
    Rectangle(int id, int x, int y, int width, int height);
    virtual void print() const;
    virtual bool is_inside(int x, int y) const;
    bool in(int x, int x0, int len) const;
    virtual void zoom(int factor);
  	virtual ~Rectangle();
  	
  private:
  	int w;
  	int h;   
};
