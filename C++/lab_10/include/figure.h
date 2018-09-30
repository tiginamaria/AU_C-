#pragma once

class Figure {
  public:
    Figure(int id, int x, int y);
    virtual ~Figure();

    virtual void print() const = 0;
    virtual bool is_inside(int x, int y) const = 0;
    virtual void zoom(int factor) = 0;
    void move(int new_x, int new_y);
	int getX() const;
	int getY() const;
	int getId() const;
	
  protected:
    int id;
    int x;
    int y;
};
