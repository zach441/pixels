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
#include <stdio.h>
#include <stdlib.h>

//gets the size of the file from the header
// todo: check it against the actual size of the file, should be the same
unsigned int getSize(FILE* myFile) {
    fseek(myFile, 2, SEEK_SET);
    unsigned int filesize = 0;
    short i;
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
    short i;
    for (i = 0; i <= 3; i++) {
        arrStart += (unsigned int) fgetc(myFile) << (i * 8);
    }
    rewind(myFile);
    return arrStart;
}

//get the header from the input image and store it to an array, mallocing enough
//memory so that we can fit the whole file in the array
char* initArray(FILE*myFile) {
    unsigned int size;
    size = getSize(myFile);
    char*array;
    array = malloc(size);
    if (array == NULL) {
        perror("error while allocating memory see input/initArray");
        exit(-1);
    }
    unsigned int i;
    for(i = 0; i <= (size-1);i++){
        *(array + i) = (char) fgetc(myFile);
    }
    rewind(myFile);
    return array;
}
