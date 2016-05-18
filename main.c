/*
 * main.c
 *
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */

#include "pixels.h"
#define debug_mode
#define dry_run
//convenient channels for multiples of three
#define bchannel (i)
#define gchannel (i+1)
#define rchannel (i+2)

int main(int argc, char** argv) {
    FILE* inF;
    inF = fopen("in.bmp", "rb");
#ifndef dry_run
    FILE* outF;
    outF = outInit("out.bmp");
#endif //dry_run

    unsigned int fileEnd = getSize(inF);
    unsigned int dataStart = getStart(inF);
    char* header = getHeader(inF);
    //for now just make a gray image that's the same size as the input
    unsigned int i;
    for (i = dataStart; i <= fileEnd + 1; i++) {
        header[i] = 0x80;
    }
    makePixelArray(inF);
    free(header);
#ifndef dry_run
    fwrite(header, 1, fileEnd, outF);
    fclose(outF);
#endif //dry_run
#ifdef debug_mode
    printf("file ends at   %x\n", fileEnd);
    printf("data starts at %x\n", dataStart);
    printf("image is %d pixels wide\n", getWidth(inF));
    printf("image is %d pixels tall\n", getHeight(inF));
    printf("image has %i pixels\n", getNumPixels(inF));
#endif //debug_mode
    fclose(inF);
    return 0;
}

//sort the array by the sum RGB values for each pixel
pixel* sumSort(pixel *array, unsigned int numel) {
    return NULL;
}

