/*
 * main.c
 *
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */

#include "pixels.h"
#include <stdio.h>
#include <stdlib.h>
#define arraystart 0x36
#define fileend 0x336
//convenient channels for multiples of three
#define bchannel (i)
#define gchannel (i+1)
#define rchannel (i+2)

int main(int argc, char** argv) {
    FILE * outf;
    outf = outInit("out.bmp");

    char* pixel_array = malloc(fileend);
    putHeaders(pixel_array);

    int i;
    unsigned char r, g, b;
    r = g = b = 0;
    for (i = arraystart; i <= (fileend - 3); i += 3) {
        short col = (i / 3) % 16;
        short row = i / 48;
        if (row == 4 && col == 12) {
            *(pixel_array + bchannel) = 0xff;
            *(pixel_array + gchannel) = 0;
            *(pixel_array + rchannel) = 0;
        } else {
            *(pixel_array + bchannel) = b++;
            *(pixel_array + gchannel) = (i % 9) * 16;
            *(pixel_array + rchannel) = r++;
        }
    }
    //then finally turn the array into an image file
    fwrite(pixel_array, 1, fileend, outf);
    fclose(outf);
    free(pixel_array);
    return 0;
}
