/*
 * input.c
 *
 *  Created on: May 13, 2016
 *      Author: Zachary
 */
#include <stdio.h>

unsigned int getSize(FILE* myFile) {
    fseek(myFile, 2, SEEK_SET);
    unsigned int filesize = 0;
    short i;
    for (i = 0; i <= 3; i++) {
        filesize += (unsigned int) fgetc(myFile) <<(i*8);
    }
    return filesize;
}

//gets the location of the start of the pixel data
unsigned int getStart(FILE*myFile) {
    fseek(myFile, 0xA, SEEK_SET);
    unsigned int arrStart = 0;
    short i;
    for (i = 0; i <= 3; i++) {
        arrStart += (unsigned int) fgetc(myFile)<<(i*8);
    }
    return arrStart;
}
