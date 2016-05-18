/*
 * output.c
 *  Some utilities for outputting to 24 bit bmp files, adding other types
 *  eventually maybe
 *  Created on: May 13, 2016
 *      Author: Zachary
 */
#include "pixels.h"

FILE* outInit(const char* name) {
    FILE* temp;
    temp = fopen(name, "wb");
    if (temp == NULL) {
        perror("could not open output file");
        exit(-3);
    }
    return temp;
}

//todo: make this less fragile
void makeImage(char* header, pixel* image, FILE* file) {
    //XXX:for some reason header[2] is reading as 0xfffffff86 instead of 0x86
    //I have no idea why, but the issue doesn't seem to be here
    //this is from the BMP header spec
    unsigned int size = header[2] + (header[3] << 8) + (header[4] << 16)
            + (header[5] << 24);
    char* wholeFile;
    wholeFile = malloc(size);
    if (wholeFile == NULL) {
        perror("issue allocating memory, output/makeimage");
        exit(-1);
    }
    //this is from the BMP header spec
    unsigned int header_size = header[10] + (header[11] << 8)
            + (header[12] << 16) + (header[13] << 24) - 1;
    unsigned int i;
    for (i = 0; i < header_size; i++) {
        wholeFile[i] = header[i];
    }
    for (i = header_size + 1; i < size; i++) {
        switch ((i - header_size) % 3) {
            case 1:
                wholeFile[i] = image[i - header_size - 1].blu;
                break;
            case 2:
                wholeFile[i] = image[i - header_size - 2].grn;
                break;
            case 3:
                wholeFile[i] = image[i - header_size - 3].red;
                break;
            default:
                perror("something has gone terribly wrong in output/makeimage");
        }
    }
}
