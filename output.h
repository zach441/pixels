/*
 * output.h
 *
 *  Created on: May 13, 2016
 *      Author: Zachary
 */
#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "pixels.h"

FILE* outInit(const char * name);
void makeImage(char*, pixel*);

#endif /* OUTPUT_H_ */
