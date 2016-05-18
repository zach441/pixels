/*
 * pixels.h
 *
 *  Created on: May 13, 2016
 *      Author: Zachary
 */

#ifndef PIXELS_H_
#define PIXELS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char red;
    unsigned char grn;
    unsigned char blu;
    unsigned int tot_rgb;
} pixel;

#include "output.h"
#include "input.h"


#endif /* PIXELS_H_ */
