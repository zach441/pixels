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
//#define dry_run

int comparePixels(const void* first, const void* second) {
	const pixel* a = first;
	const pixel* b = second;
	if(a -> tot_rgb < b -> tot_rgb) return -1;
	if(a -> tot_rgb > b -> tot_rgb) return 1;
	return 0;
}

int main(int argc, char** argv) {
    char* inName = malloc(64);
    char* outName = malloc(64);
    //64 characters should be enouth for a file name, maybe change later -z
   
    if(argc != 1) {
        switch(argc) {
            case 2:
                //todo: adda a way to get to a help message
                inName = argv[1];
                outName = "out.bmp";
                break;
            case 3: 
                inName = argv[1];
                outName = argv[2];
                break;
            default:
                puts("you did too many args, how did you even???");
                //todo make this go to ahelp message
                exit(0);
        }

    } else {
        inName = "in.bmp";
        outName = "out.bmp";
    }
    setbuf(stdout, NULL);
    FILE* inF;
    inF = inInit(inName);
#ifndef dry_run
    FILE* outF;
    outF = outInit(outName);
#endif //dry_run
    unsigned char* header = getHeader(inF);
    pixel* image = makePixelArray(inF);
    //now we'll try and sort the pixels
    qsort(image,getNumPixels(inF), sizeof(pixel), comparePixels); 

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
