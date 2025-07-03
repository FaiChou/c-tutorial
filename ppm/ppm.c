#include "ppm.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/mman.h>

ppm_image *ppm_readimage(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    // get the file size
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    
    // get file descriptor
    int fd = fileno(file);

    rewind(file);

    ppm_image *result = malloc(sizeof *result);

    // get magic number
    char type[3] = {0};
    if (fscanf(file, "%2s", type) != 1) {
        perror("Failed to read magic number");
        free(result);
        fclose(file);
        return NULL;
    }

    if (strcmp(type, "P6") != 0) {
        perror("Invalid PPM file");
        free(result);
        fclose(file);
        return NULL;
    }

    // get dimensions
    if (fscanf(file, "%zu %zu", &result->cols, &result->rows) != 2) {
        perror("Failed to read dimensions");
        free(result);
        fclose(file);
        return NULL;
    }

    // get maxval
    if (fscanf(file, "%hu", &(result->maxval)) != 1) {
        perror("Failed to read maxval");
        free(result);
        fclose(file);
        return NULL;
    }

    off_t offset = ftell(file);

    uint8_t *rawdata = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (rawdata == MAP_FAILED) {
        perror("Failed to map file into memory");
        free(result);
        fclose(file);
        return NULL;
    }
    
    uint8_t bytes_per_value = (result->maxval > 255) ? 2 : 1;
    const int values_per_pixel = 3;

    uint8_t *pixeldata = rawdata + offset + 1;

    result->pixels = calloc(result->rows, sizeof(pixel *));
    for (size_t i = 0; i < result->rows; i++) {
        result->pixels[i] = calloc(result->cols, sizeof(pixel));
    }

    for (size_t i = 0; i < result->rows; i++) {
        for (size_t j = 0; j < result->cols; j++) {
            if (bytes_per_value == 1) {
                result->pixels[i][j].r = pixeldata[0];
                result->pixels[i][j].g = pixeldata[1];
                result->pixels[i][j].b = pixeldata[2];
            } else {
                result->pixels[i][j].r = pixeldata[0] << 8 | pixeldata[1];
                result->pixels[i][j].g = pixeldata[2] << 8 | pixeldata[3];
                result->pixels[i][j].b = pixeldata[4] << 8 | pixeldata[5];
            }
            pixeldata += values_per_pixel * bytes_per_value;
        }
    }

    munmap(rawdata, file_size);
    fclose(file);
    return result;
}

void ppm_destroy(ppm_image *image) {
    for (size_t i = 0; i < image->rows; i++) {
        free(image->pixels[i]);
    }
    free(image->pixels);
}
bool ppm_writeimage(const char *filename, const ppm_image *image) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return false;
    }

    if (fprintf(file, "P6\n%zu %zu\n%u\n", image->cols, image->rows, image->maxval) < 0) {
        perror("Failed to write header");
        fclose(file);
        return false;
    }

    uint8_t bytes_per_value = (image->maxval > 255) ? 2 : 1;
    for (size_t i = 0; i < image->rows; i++) {
        for (size_t j = 0; j < image->cols; j++) {
            fwrite(&(image->pixels[i][j].r), bytes_per_value, 1, file);
            fwrite(&(image->pixels[i][j].g), bytes_per_value, 1, file);
            fwrite(&(image->pixels[i][j].b), bytes_per_value, 1, file);
        }
    }
    fclose(file);
    return true;
}
