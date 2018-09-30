#ifndef _BOARDTEST_H_INCLUDED
#define _BOARDTEST_H_INCLUDED

#include "Test.h"
#include <cstddef>

class BoardTest : public Test {
public:
    void runAllTests();
    void moveTest1();
    void moveTest2();
    void moveTest3();
    void getCellTest1();
    void getCellTest2();
    void getCellTest3();
    void canMoveTest1();
    void canMoveTest2();
    void canMoveTest3();
    void getstatusTest1();
    void getstatusTest2();
    void getstatusTest3();
};

#endif
