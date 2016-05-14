/*
 * input.h
 *
 *  Created on: May 13, 2016
 *      Author: Zachary
 */
#include <stdio.h>
#ifndef INPUT_H_
#define INPUT_H_
unsigned long int getSize(FILE* myFile);
unsigned long int getStart(FILE* myFile);

char* getFile(FILE* myFile);


#endif /* INPUT_H_ */
