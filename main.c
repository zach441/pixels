/*
 * main.c
 *
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */

#include "pixels.h"
#include "output.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

//#define debug_mode
#define dry_run

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
    unsigned char* header = getHeader(inF);
    pixel* image = makePixelArray(inF);
#ifdef debug_mode
    puts("made pixel array, contents:");
    int foo;
    for (foo = 0; foo < getNumPixels(inF); foo++) {
        printf("pix #%02d value %02x %02x %02x\n", foo, image[foo].blu,
                image[foo].grn, image[foo].red);
    }
    printf("file ends at   %x\n", fileEnd);
    printf("data starts at %x\n", dataStart);
    printf("image is %d pixels wide\n", getWidth(inF));
    printf("image is %d pixels tall\n", getHeight(inF));
    printf("image has %u pixels\n", getNumPixels(inF));
#endif //debug_mode
#ifndef dry_run
    makeImage(header, image, outF);
    fclose(outF);
#endif// dry_run
    fclose(inF);
    free(header);
    free(image);
    return EXIT_SUCCESS;
}
