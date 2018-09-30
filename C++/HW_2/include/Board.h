#ifndef _BOARD_H_INCLUDED
#define _BOARD_H_INCLUDED

#include <cstddef>

enum status {XWIN, OWIN, DRAW, CONTINIUE};

const int BOARD_SIZE = 10;
const int WIN_SCORE = 5;

class  History {
public:
	char player;
	int lastR;
	int lastC;
};

class  Board {
private:
	char b[10][10]; 
	History h[101];
	int nMove = 0;
	bool checkMainDiag(int row, int col, char sign);
	bool checkAntiDiag(int row, int col, char sign);
	bool checkRow(int col, char sign);
	bool checkCol(int row, char sign);
	void gameRollback();
	void showHistory();
	void AddToHistory(int row, int col, char sign); 
	bool continueGame();
	bool Win();
	bool checkWin(int result);
	
public:
	Board();
	char getCell(int row, int col);
    void move(int row, int col, char sign); //сделать ход
    bool canMove(int row, int col); //корректен ли ход
    status gameStatus(); // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли
};

#endif
