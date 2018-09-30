#include "algorithm"
#include "BoardView.h"
#include "Board.h"
#include <stdio.h>
#include <assert.h>	

View::View(Board *board) {
	b = board;
}

void View::showBoard() {
	printf("\n");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++)
			printf("%c", b->getCell(i, j));
		printf("\n");
	}		
}

void View::doGameCycle(bool silent) {
	int row;
	int col;
	char curplayer = 'X';
	while (b->gameStatus() == CONTINIUE) {
		curplayer = curplayer == 'O' ? 'X' : 'O';
		if (!silent)
			showBoard();
		printf("%c move: ", curplayer);
		while (scanf("%d %d", &row, &col) && (row != -1 || col != -1) && !b->canMove(row, col)) {
            printf("Bad move!\n");
            printf("%c move: ", curplayer);
        }  
        
        if (row == -1 && col == -1)
			return; 	
		b->move(row, col, curplayer);	
	}
	showBoard();
	status st = b->gameStatus();
	if (st == XWIN)
		printf("X wins!\n");
	if (st == OWIN)
		printf("O wins!\n");
	if (st == DRAW)
		printf("Draw.\n");
}
		
