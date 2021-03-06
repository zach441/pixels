/*
 * input.h
 *  Header file for input.c, prototypes &c.
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */
#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include "pixels.h"

FILE* inInit(const char* name);
unsigned int getSize(FILE*);
unsigned int getStart(FILE*);
signed int getWidth(FILE*);
signed int getHeight(FILE*);
unsigned int getNumPixels(FILE*);

unsigned char* getHeader(FILE*);
pixel *makePixelArray(FILE*);

#endif /* INPUT_H_ */
