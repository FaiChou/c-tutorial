#ifndef PPM_H
#define PPM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    uint16_t r;
    uint16_t g;
    uint16_t b;
} pixel;

typedef struct {
    size_t rows;
    size_t cols;
    uint16_t maxval;

    pixel **pixels;
} ppm_image;

ppm_image *ppm_readimage(const char *filename);
void ppm_destroy(ppm_image *image);
bool ppm_writeimage(const char *filename, const ppm_image *image);

#endif