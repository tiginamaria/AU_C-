#ifndef _BOARDVIEW_H_INCLUDED
#define _BOARDVIEW_H_INCLUDED

#include "Board.h"
#include <cstddef>

class View {
private:
	Board *b;
	
public:
	View(Board *board);
	void showBoard(); 
	void doGameCycle(bool silent); 
};

#endif
