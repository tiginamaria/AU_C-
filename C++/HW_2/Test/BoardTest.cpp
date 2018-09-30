#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include "BoardTest.h"
#include "BoardView.h"
#include "Board.h"

void BoardTest::runAllTests() {
    moveTest1();
    moveTest2();
    moveTest3();
    getCellTest1();
    getCellTest2();
    getCellTest3();
    canMoveTest1();
    canMoveTest2();
    canMoveTest3();
    getstatusTest1();
    getstatusTest2();
    getstatusTest3();
}
	
void BoardTest::moveTest1() {
    Board b;
    b.move(2, 2, 'O');
    DO_CHECK(b.getCell(2, 2) == 'O');
}
void BoardTest::moveTest2() {
    Board b;
    b.move(7, 2, 'X');
    DO_CHECK(b.getCell(7, 2) == 'X');
}
void BoardTest::moveTest3() {
    Board b;
    b.move(7, 9, 'O');
	DO_CHECK(b.getCell(7, 9) == 'O');
}


void BoardTest::getCellTest1() {
    Board b;
    b.move(3, 7, '.');
    DO_CHECK(b.getCell(9, 8) == '.');
}
void BoardTest::getCellTest2() {
    Board b;
    b.move(0, 0, 'X');
    DO_CHECK(b.getCell(0, 0) == 'X');
}
void BoardTest::getCellTest3() {
    Board b;
    b.move(9, 8, 'O');
    DO_CHECK(b.getCell(9, 8) == 'O');
}

void BoardTest::canMoveTest1() {
    Board b;
    DO_CHECK(b.canMove(4, 9) == true);
}
void BoardTest::canMoveTest2() {
    Board b;
    b.move(0, 0, 'X');
    DO_CHECK(b.canMove(0, 0) == false);
}
void BoardTest::canMoveTest3() {
    Board b;
    b.move(9, 8, 'O');
    DO_CHECK(b.canMove(9, 8) == false);
}

void BoardTest::getstatusTest1() {
    Board b;            //  0123456789
    b.move(0, 4, 'O');  //0 X...0.....
    b.move(0, 0, 'X');  //1 .X...0....
    b.move(1, 5, 'O');  //2 ..X...OO..
    b.move(1, 1, 'X');  //3 ...X...0..
    b.move(2, 7, 'O');  //4 ....X.....
    b.move(2, 2, 'X');  //5 ..........
    b.move(2, 6, 'O');  //6 ..........
    b.move(3, 3, 'X');  //7 ..........
    b.move(3, 7, 'O');  //8 ..........
    b.move(4, 4, 'X');  //9 ..........
    DO_CHECK(b.gameStatus() == XWIN);
}

void BoardTest::getstatusTest2() {
    Board b;            //  0123456789
    b.move(2, 3, 'O');  //0 ..........
    b.move(1, 3, 'X');  //1 ...X......
    b.move(4, 5, 'O');  //2 ...O......
    b.move(3, 3, 'X');  //3 ...X......
    b.move(4, 1, 'O');  //4 .OOXOO....
    b.move(4, 3, 'X');  //5 ...X......
    b.move(4, 2, 'O');  //6 ...X......
    b.move(5, 3, 'X');  //7 ..........
    b.move(4, 4, 'O');  //8 ..........
    b.move(6, 3, 'X');  //9 ..........
    DO_CHECK(b.gameStatus() == CONTINIUE);
}

void BoardTest::getstatusTest3() {
    Board b;          
    b.move(6, 6, 'O');  //  0123456789
    b.move(6, 3, 'X');  //0 ..........
    b.move(7, 5, 'O');  //1 ...X......
    b.move(6, 2, 'X');  //2 ..........
    b.move(8, 4, 'O');  //3 ..........
    b.move(7, 3, 'X');  //4 ..........
    b.move(5, 7, 'O');  //5 .......O..
    b.move(1, 3, 'X');  //6 ..XX..O...
    b.move(9, 3, 'O');  //7 ...X.O....
    					//8 ....O.....
    					//9 ...O......
    DO_CHECK(b.gameStatus() == OWIN);
}

