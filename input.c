/*
 * input.c
 *  Defines some utilities for inputting files, currently only for 24 bit *.bmp
 *  type files, other types to be added in a later release.
 *
 *  TODO: error on bad files
 *
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */

#include "pixels.h"

//gets the size of the file from the header
// todo: check it against the actual size of the file, should be the same
unsigned int getSize(FILE* myFile) {
    fseek(myFile, 2, SEEK_SET);
    unsigned int filesize = 0;
    char i;
    for (i = 0; i <= 3; i++) {
        filesize += (unsigned int) fgetc(myFile) << (i * 8);
    }
    rewind(myFile);
    return filesize;
}

//gets the location of the start of the pixel data from the file
unsigned int getStart(FILE*myFile) {
    fseek(myFile, 0xA, SEEK_SET);
    unsigned int arrStart = 0;
    char i;
    for (i = 0; i <= 3; i++) {
        arrStart += (unsigned int) fgetc(myFile) << (i * 8);
    }
    rewind(myFile);
    return arrStart;
}

//gets the width of the image (in pixels) from the header data
//this is signed because it's signed in the spec
signed int getWidth(FILE* myFile) {
    fseek(myFile, 0x12, SEEK_SET);
    signed int width = 0;
    char i;
    for (i = 0; i <= 3; i++) {
        width += (signed int) (fgetc(myFile) << (i * 8));
    }
    rewind(myFile);
    return width;
}

//gets the height of the image in pixels fro mthe header data
//signed because it is in the spec
signed int getHeight(FILE* myFile) {
    fseek(myFile, 0x12, SEEK_SET);
    signed int height = 0;
    char i;
    for (i = 0; i <= 3; i++) {
        height += (signed int) fgetc(myFile) << (i * 8);
    }
    rewind(myFile);
    return height;
}

unsigned int getNumPixels(FILE* myFile) {
    return (getWidth(myFile) * getHeight(myFile));
}

//get the header from the input image and store it to an array, mallocing enough
//memory so that we can fit the whole file in the array
char* getHeader(FILE*myFile) {
    unsigned int size;
    size = getSize(myFile);
    char*array;
    array = malloc(size);
    if (array == NULL) {
        perror("error while allocating memory see input/initArray");
        exit(-1);
    }
    unsigned int i;
    for (i = 0; i < size; i++) {
        *(array + i) = (char) fgetc(myFile);
    }
    rewind(myFile);
    return array;
}

//todo: make this more efficient
pixel* makePixelArray(FILE* myFile) {
    signed int height = getHeight(myFile);
    signed int width = getWidth(myFile);

    //see wikipedia article /wiki/BMP_file_format for why this works
    unsigned int rowSize = ((24 * width + 31) / 32) * 4;
    unsigned int arraySize = rowSize * height;
    printf("rowSize is %d, arraySize is %d\n", rowSize, arraySize);
    pixel* image;
    unsigned int numPix = getNumPixels(myFile);
    image = malloc((sizeof(pixel)) * (numPix));
    if (image == NULL) {
        perror("error allocating memory (input/makePixelArray)");
        exit(-2);
    }

    fseek(myFile, getStart(myFile), SEEK_SET);

    unsigned int i, whichByte = 0;
    for (i = 0; whichByte < arraySize; i++) {
        if ((whichByte % rowSize) < (width*3)) {
            image[i].blu = fgetc(myFile);
            image[i].grn = fgetc(myFile);
            image[i].red = fgetc(myFile);
            image[i].tot_rgb = image[i].blu + image[i].grn + image[i].red;
            printf(
                    "pixel number %3i has value %02x %02x %02x for a total of %x\n",
                    i, image[i].red, image[i].grn, image[i].blu,
                    image[i].tot_rgb);
            whichByte += 3;
        } else {
            fgetc(myFile);
            whichByte += 1;
            printf("padding\n");
        }
    }

    return image;
}
