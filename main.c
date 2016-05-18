/*
 * main.c
 *
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */

#include "pixels.h"
#define debug_mode
//#define dry_run

int main(int argc, char** argv) {
    setbuf(stdout, NULL);
    FILE* inF;
    inF = inInit("in.bmp");
#ifndef dry_run
    FILE* outF;
    outF = outInit("out.bmp");
#endif //dry_run
    unsigned int fileEnd = getSize(inF);
    unsigned int dataStart = getStart(inF);
    //code goes here
    char* header = getHeader(inF);
    puts("got header");
    pixel* image = makePixelArray(inF);
    makeImage(header, image, outF);
#ifndef dry_run
    fclose(outF);
#endif// dry_run
#ifdef debug_mode
    printf("file ends at   %x\n", fileEnd);
    printf("data starts at %x\n", dataStart);
    printf("image is %d pixels wide\n", getWidth(inF));
    printf("image is %d pixels tall\n", getHeight(inF));
    printf("image has %i pixels\n", getNumPixels(inF));
#endif //debug_mode
    fclose(inF);
    free(header);
    free(image);
    return EXIT_SUCCESS;
}
