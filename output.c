/*
 * output.c
 *  Some utilities for outputting to 24 bit bmp files, adding other types
 *  eventually maybe
 *  Created on: May 13, 2016
 *      Author: Zachary
 */
#include "pixels.h"
#include <stdio.h>
#include <stdlib.h>
//#define debug_mode
//#define verbose_deb
FILE* outInit(const char* name) {
    FILE* temp;
    temp = fopen(name, "wb");
    if (temp == NULL) {
        perror("could not open output file");
        exit(-3);
    }
    return temp;
}

void makeImage(unsigned char* header, pixel* image, FILE* file) {
    //this is from the BMP header spec
    unsigned int size = header[2] + (header[3] << 8) + (header[4] << 16)
            + (header[5] << 24);
    char* wholeFile;
#ifdef debug_mode
    printf("trying to malloc %u bytes\n", size);
#endif
    wholeFile = malloc(size);
#ifdef debug_mode
    puts("malloc executed");
#endif
    if (wholeFile == NULL) {
        perror("issue allocating memory, output/makeimage");
        exit(-1);
    }
#ifdef debug_mode
    printf("Successfully malloced %u bytes\n", size);
#endif
    //this is from the BMP header spec
    unsigned int headerSize = header[10] + (header[11] << 8)
            + (header[12] << 16) + (header[13] << 24) - 1;
    unsigned int i;
    //write the header
    for (i = 0; i <= headerSize; i++) {
        wholeFile[i] = header[i];
    }

    signed int width = header[0x12] + (header[0x13] << 8) + (header[0x14] << 16)
            + (header[0x15] << 24);
    i = headerSize + 1;

    //see wikipedia article /wiki/BMP_file_format for why this works
    unsigned int rowSize = (((24 * width) + 31) / 32) * 4;
#ifdef debug_mode
    printf("the size of a row is %d bytes\n", rowSize);
#ifdef verbose_deb
    puts("what follows is offset from the end of the header");
#endif
#endif
    unsigned int whichPix = 0;
    //write the rest of the image
    while (i < size) {
#ifdef debug_mode
#ifdef verbose_deb
        printf("%i\n", i - headerSize);
#endif
#endif
        if (((i - headerSize - 1) % rowSize) < (width * 3)) {
            wholeFile[i++] = image[whichPix].blu;
            wholeFile[i++] = image[whichPix].grn;
            wholeFile[i++] = image[whichPix].red;
            whichPix++;
        } else {
            wholeFile[i] = 0x0;
            i++;
        }
    }
    fwrite(wholeFile, sizeof(char), size, file);
}
