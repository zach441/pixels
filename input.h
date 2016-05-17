/*
 * input.h
 *  Header file for input.c, prototypes &c.
 *  Created on: May 13, 2016
 *      Author: Zach Oakes
 */
#include <stdio.h>
#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
unsigned int getSize(FILE*);
unsigned int getStart(FILE*);
char* initArray(FILE*);

#endif /* INPUT_H_ */
