/*
 * output.c
 *
 *  Created on: May 13, 2016
 *      Author: Zachary
 */
#include <stdio.h>

FILE* outInit(const char* name) {
    return fopen(name, "wb");
}

void putHeaders(char* filearray) {
    //this is the bitmap header, see
    //https://en.wikipedia.org/wiki/BMP_file_format
    //for details
    char header[] =
            { 0x42, 0x4d, 0x36, 0x03, 0, 0, 0, 0, 0, 0, 0x36, 0, 0, 0, 0x28, 0,
                    0, 0, 0x10, 0, 0, 0, 0x10, 0, 0, 0, 0x01, 0, 0x18, 0, 0, 0,
                    0, 0, 0, 0x03, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0 };
    int i;
    //write the header stuff to the array
    for (i = 0; i <= 0x35; i++) {
        *(filearray + i) = header[i];
    }
}
