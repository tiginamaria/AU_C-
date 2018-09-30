#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bmp.h"

int add_padding(int l) {
  	return (3 * l + 3) & (-4);
}

int calc_size(int h, int w) {
	return h * w;
}

void free_memory(Image *pic, Image *new_pic) {
	free(pic->img);
	free(new_pic->img);
}

void appdate_header(Image *pic, int h, int w, int size) {
	pic->info.height = h;
    pic->info.width = w;
    pic->file.size = size + 54;
    pic->info.bitmap_size = size;
}

int load_bmp(char* path, Image *pic) {

    FILE* file = fopen(path, "rb");
    if(file == NULL) {
		printf("error_load_file");
		return 1;
	}

    fread(&(pic->file), sizeof(BmpFileHeader), 1, file);
    fread(&(pic->info), sizeof(BmpInfoHeader), 1, file);

    int W = pic->info.width;
    int H = pic->info.height;
	int size = calc_size(add_padding(W), H);

    pic->img = (unsigned char*)malloc(size);
	if (pic->img == NULL) {
		printf("error_load_memory");
		return 1;
	}
	memset(pic->img, 0, size);

    fread(pic->img, 1, size, file);
    fclose(file);
    return 0;
}

int save_bmp(char* path, Image *new_pic) {

    FILE* file = fopen(path, "wb");
    if(file == NULL) {
		printf("error_save_file");
		return 1;
	}

    int W = new_pic->info.width;
    int H = new_pic->info.height;
	int size = calc_size(add_padding(W), H);

    fwrite(&new_pic->file, sizeof(BmpFileHeader), 1, file);
    fwrite(&new_pic->info, sizeof(BmpInfoHeader), 1, file);
    fwrite(new_pic->img, sizeof(char), size, file);

    fclose(file);
    return 0;
}

int crop_bmp(Image *pic, Image *new_pic, int x, int y, int w, int  h) {
    long long i;

    memcpy(&new_pic->file, &pic->file, sizeof(BmpFileHeader));
    memcpy(&new_pic->info, &pic->info, sizeof(BmpInfoHeader));

	int W = pic->info.width;
    int H = pic->info.height;
	int size = calc_size(add_padding(W), H);

	if (x + w > W || y + h > H) {
		printf("error_crop_wrong_size");
		return 1;
	}

	appdate_header(new_pic, h, w, size);
    y = H - y - h;

	new_pic->img =(unsigned char*)malloc(size);
	memset(new_pic->img, 0, size);
	if (new_pic->img == NULL) {
		printf("error_crop_memory");
		return 1;
	}

    for (i = 0; i < h; i++) {
        memcpy(&(new_pic->img[i * add_padding(w)]), &(pic->img[3 * x + (y + i) *  add_padding(W)]), add_padding(w));
    }
    return 0;
}

int rotate_bmp(Image *new_pic) {
    long long i, j;

    int w = new_pic->info.width;
    int h = new_pic->info.height;
	int size = calc_size(add_padding(h), w);

    unsigned char *buf =(unsigned char*)malloc(size);
	memset(buf, 0, size);
	if (buf == NULL) {
		printf("error_rotate_memory");
		return 1;
	}

    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++) {
            memcpy(&buf[((w - j - 1) * add_padding(h) + 3 * i)], &(new_pic->img[i * add_padding(w) + 3 * j]), 3);
        }

    free(new_pic->img);
    new_pic->img = buf;
	appdate_header(new_pic, w, h, size);
    return 0;
}
