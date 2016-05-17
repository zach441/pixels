/*
 * main.c
 *
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */

#include "pixels.h"
#include <stdio.h>
#include <stdlib.h>
//convenient channels for multiples of three
#define bchannel (i)
#define gchannel (i+1)
#define rchannel (i+2)

int main(int argc, char** argv) {
    FILE* inF;
    FILE* outF;
    inF = fopen("in.bmp", "rb");
    outF = outInit("out.bmp");
    unsigned int fileEnd = getSize(inF);
    printf("file ends at   %x\n", fileEnd);
    unsigned int dataStart = getStart(inF);
    printf("data starts at %x\n", dataStart);
    char* file_array = initArray(inF);

    //for now just make a gray image that's the same size as the input
    unsigned int i;
    for(i = dataStart; i <= fileEnd + 1; i++){
        file_array[i] = 0x80;
    }
    fwrite(file_array, 1, fileEnd, outF);

    fclose (inF);
    fclose(outF);
    free(file_array);
    return 0;
}
