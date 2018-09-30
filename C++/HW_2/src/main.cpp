#include "BoardView.h"
#include "string.h"

int main(int argc, char **argv) {
	bool silent = (argc == 2 && !strcmp("silent", argv[1]));
    Board b;
    View v(&b);
    v.doGameCycle(silent);
    return 0;
}
