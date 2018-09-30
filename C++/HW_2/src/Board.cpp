#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include "Board.h"


Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			b[i][j] = '.';
	h[nMove].lastR = 0;
	h[nMove].lastC = 0;
	h[nMove].player = 'X';
}

void Board::AddToHistory(int row, int col, char sign) {
	nMove++;
	h[nMove].lastR = row;
	h[nMove].lastC = col;
	h[nMove].player = sign;
}

void Board::gameRollback() {
	h[nMove].lastR = 0;
	h[nMove].lastC = 0;
	nMove--;
}

void Board::showHistory() {
	printf("# Player   ROW    COL\n");
	for (int i = 1; i <= nMove; i++)
		printf("%d    %c      %d      %d \n", i, h[i].player, h[i].lastR, h[i].lastC );
}

void Board::move(int row, int col, char sign) {
	b[row][col] = sign;
	AddToHistory(row, col, sign);
} 

char Board::getCell(int row, int col) {
	return b[row][col];
} 

bool Board::canMove(int row, int col) {
	return row < BOARD_SIZE && row >= 0 && col < BOARD_SIZE && col >= 0 && b[row][col] == '.';
}

bool Board::checkWin(int result) { 
	return result >= WIN_SCORE;
}
	
bool Board::Win() {
	char sign = h[nMove].player;
	int row = h[nMove].lastR;
	int col = h[nMove].lastC;
	return (checkRow(col, sign) || checkCol(row, sign) || 
					     checkMainDiag(row, col, sign) || checkAntiDiag(row, col, sign));
}

bool Board::checkRow(int col, char sign) {
	int score = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
		if (b[i][col] == sign) 
			score++;
		else if (checkWin(score)) 
			return true;
		else 
			score = 0;
	if (checkWin(score)) 
		return true;
	return false;
}
	
bool Board::checkCol(int row, char sign) {	
	int score = 0;
	for (int j = 0; j < BOARD_SIZE; j++)
		if (b[row][j] == sign) 
			score++;
		else if (checkWin(score)) 
			return true;
		else 
			score = 0;
	if (checkWin(score)) 
		return true;
	return false;
}

bool Board::checkMainDiag(int row, int col, char sign) {
	int i, j;
	int score = 0;
	if (row > col) {
		i = row - col;
		j = 0;
	}
	else {
		i = 0;
		j = col - row;
	}
	while(i < BOARD_SIZE && j < BOARD_SIZE) {
		if (b[i][j] == sign) 
			score++;
		else if (checkWin(score)) 
			return true;
		else 
			score = 0;
		i++; j++;
	}
	if (checkWin(score)) return true;
	return false;
}
	
bool Board::checkAntiDiag(int row, int col, char sign) {
	int i, j;
	int score = 0;	
	if (row + col < BOARD_SIZE) {
		i = 0;
		j = row + col;
	}
	else {
		i = row + col - BOARD_SIZE + 1;
		j = BOARD_SIZE - 1;
	}
	while(i < BOARD_SIZE && j >= 0) {
		if (b[i][j] == sign) 
			score++;
		else if (checkWin(score)) 
			return true;
		else 
			score = 0;
		i++; j--;
	}
	if (checkWin(score)) 
		return true;
	return false;
}
	
bool Board::continueGame() {
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			if (b[i][j] == '.')
				return true;
	return false;
}

status Board::gameStatus() {
	if (h[nMove].player == 'X' && Win())
		return XWIN;
	if (h[nMove].player == 'O' && Win())
		return OWIN;		
	if (continueGame())
		return CONTINIUE;
	return DRAW;
}
