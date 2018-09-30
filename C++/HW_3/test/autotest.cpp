#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include "autotest.h"

int Test::totalNum = 0;
int Test::failedNum = 0;

void Test::check(bool expr, const char *function, const char *filename, size_t lineNum) {
    totalNum++;
    if (expr)
        return;
    printf("Test failed: %s in %s:%zd\n", function, filename, lineNum);
    failedNum++;
}

void Test::showFinalResult() {
	if (!failedNum)
	 	printf("All test passed.\n");
	else
		printf("Failed %d of %d tests.\n", failedNum, totalNum);
}
