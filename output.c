/*
 * output.c
 *
 *  Created on: May 13, 2016
 *      Author: Zachary
 */
#include "pixels.h"

FILE* outInit(const char* name) {
    return fopen(name, "wb");
}

void makeImage(char* header, pixel* image){
    //todo:this
}
