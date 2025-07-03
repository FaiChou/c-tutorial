#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include <math.h>
#include <libgen.h>

#define COLOR_WHEEL_SEGMENTS 6
pixel hueToRGB(double hue) {
    pixel color;
    double r, g, b;
    double value = 1.0; // full value/brightness
    int segment = floor(hue * COLOR_WHEEL_SEGMENTS);
    double offset = hue * COLOR_WHEEL_SEGMENTS - segment;

    switch (segment % COLOR_WHEEL_SEGMENTS) {
        case 0: r = value; g = offset; b = 0; break; // red
        case 1: r = (1 - offset); g = value; b = 0; break; // yellow
        case 2: r = 0; g = value; b = offset; break; // green
        case 3: r = 0; g = (1 - offset); b = value; break; // cyan
        case 4: r = offset; g = 0; b = value; break; // blue
        case 5: r = value; g = 0; b = 1 - offset; break; // magenta
        default: r = 0; g = 0; b = 0; break;
    }

    color.r = (int)(r * 255.0);
    color.g = (int)(g * 255.0);
    color.b = (int)(b * 255.0); 
    return color;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    char *output_filename = NULL;
    asprintf(&output_filename, "rainbow_%s", basename(filename));
    printf("input:\t%s\noutput:\t%s\n", filename, output_filename);

    ppm_image *image = ppm_readimage(filename);
    for (size_t i = 0; i < image->cols; i++) {
        for (size_t j = 0; j < image->rows; j++) {
            double hue = ((double)j) / ((double)image->rows);
            pixel color = hueToRGB(hue);
            const double weight = 0.3;
            image->pixels[j][i].r = (uint16_t)(color.r * weight + image->pixels[j][i].r * (1 - weight));
            image->pixels[j][i].g = (uint16_t)(color.g * weight + image->pixels[j][i].g * (1 - weight));
            image->pixels[j][i].b = (uint16_t)(color.b * weight + image->pixels[j][i].b * (1 - weight));
        }
    }
    ppm_writeimage(output_filename, image);
    ppm_destroy(image);
    return EXIT_SUCCESS;
}