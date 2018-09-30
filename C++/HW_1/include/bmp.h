#ifndef __BMPH
#define __BMPH

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#pragma pack(push, 1)

typedef struct BmpFileHeader {
    char b1, b2; 
    int32_t size; 
    int16_t not_use1; 
    int16_t not_use2; 
    int32_t mass_pos;
} BmpFileHeader;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct BmpInfoHeader {
    int32_t header_length; 
    int32_t width; 
    int32_t height; 
    int16_t color_plane_number; 
    int16_t bit_per_pixel; 
    int32_t compress_method; 
    int32_t bitmap_size; 
    int32_t mass_width; 
    int32_t mass_height;
    int32_t color_number; 
    int32_t general_color_number; 
} BmpInfoHeader;

typedef struct Image{
    BmpFileHeader file;
    BmpInfoHeader info;
    unsigned char* img;
} Image;

#pragma pack(pop)
int load_bmp(char* path, Image *pic);
int save_bmp(char* path, Image *pic);
int crop_bmp(Image *pic, Image *new_pic, int x, int y, int w, int  h);
int rotate_bmp(Image *new_pic);
void free_memory(Image *pic, Image *new_pic);
#endif
