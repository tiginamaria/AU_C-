#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"

int main(int argc, char **argv)
{
    Image pic;

    if (load_bmp(argv[2], &pic)) return 1;

    Image new_pic;

	int x = atoi(argv[4]);
	int y = atoi(argv[5]);
	int w = atoi(argv[6]);
	int h = atoi(argv[7]);

    if (crop_bmp(&pic, &new_pic, x, y, w, h)) return 1;

    if (rotate_bmp(&new_pic)) return 1;

    if (save_bmp(argv[3], &new_pic)) return 1;

	free_memory(&pic, &new_pic);

    return 0;
}

