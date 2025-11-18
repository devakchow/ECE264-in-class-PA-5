
#ifndef BMP_H
#define BMP_H
#include <stdint.h>
typedef struct {
    uint8_t r,g,b;
} Pixel;

typedef struct {
    int width,height;
    Pixel *pixels;
} BMPImage;

BMPImage read_bmp(const char *path);
void write_bmp(const char *path, BMPImage *img);
void free_image(BMPImage *img);

#endif
