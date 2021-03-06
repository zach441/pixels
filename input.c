/*
 * input.c
 *	Defines some utilities for inputting files, currently only for 24 bit *.bmp
 *	type files, other types to be added in a later release.
 *
 *	TODO: error on bad files
 *  TODO: check that files are of the 24bit bmp format, I think this can be...
 *        read in from the header
 *
 *	Created on: May 13, 2016
 *		Author: Zach Oakes
 */

#include "pixels.h"
#include <stdio.h>
#include <stdlib.h>

FILE* inInit(const char* name) {
	FILE* temp;
	temp = fopen(name, "rb");
	if (temp == NULL) {
		perror("could not open input file");
		exit(-4);
	}
	return temp;
}

//gets the size of the file from the header
// todo: check it against the actual size of the file, should be the same
unsigned int getSize(FILE* myFile) {
	fseek(myFile, 2, SEEK_SET);
	unsigned int filesize = 0;
	char i;
	for (i = 0; i <= 3; i++) {
		filesize += (unsigned int) fgetc(myFile) << (i * 8);
	}
	rewind(myFile);
	return filesize;
}

//gets the location of the start of the pixel data from the file
unsigned int getStart(FILE*myFile) {
	fseek(myFile, 0xA, SEEK_SET);
	unsigned int arrStart = 0;
	char i;
	for (i = 0; i <= 3; i++) {
		arrStart += (unsigned int) fgetc(myFile) << (i * 8);
	}
	rewind(myFile);
	return arrStart;
}

//gets the width of the image (in pixels) from the header data
//this is signed because it's signed in the spec
signed int getWidth(FILE* myFile) {
	fseek(myFile, 0x12, SEEK_SET);
	signed int width = 0;
	char i;
	for (i = 0; i <= 3; i++) {
		width += (signed int) (fgetc(myFile) << (i * 8));
	}
	rewind(myFile);
	return width;
}

//gets the height of the image in pixels from the header data
//signed because it is in the spec
signed int getHeight(FILE* myFile) {
	fseek(myFile, 0x16, SEEK_SET);
	signed int height = 0;
	char i;
	for (i = 0; i <= 3; i++) {
		height += (signed int) fgetc(myFile) << (i * 8);
	}
	rewind(myFile);
	return height;
}

unsigned int getNumPixels(FILE* myFile) {
	return (getWidth(myFile) * getHeight(myFile));
}

//get the header from the input image and store it to an array, mallocing enough
//memory so that we can fit the whole file in the array
unsigned char* getHeader(FILE*myFile) {
	unsigned int size;
	size = getStart(myFile) - 1;
	unsigned char*array;
	array = malloc(size);
	if (array == NULL) {
		perror("error while allocating memory see input/initArray");
		exit(-1);
	}
	unsigned int i;
	for (i = 0; i < size; i++) {
		char temp = fgetc(myFile);
		if (temp != EOF) {
			*(array + i) = temp;
		} else {
			perror("error in input/getHeader, end of file reached");
			exit(-3);
		}
	}
	rewind(myFile);
	return array;
}

//todo: make this more efficient
pixel* makePixelArray(FILE* myFile) {
	signed int height = getHeight(myFile);
	signed int width = getWidth(myFile);

	//see wikipedia article /wiki/BMP_file_format for why this works
	unsigned int rowSize = (((24 * width) + 31) / 32) * 4;
	unsigned int paddingLen = (rowSize - (width * 3));

	pixel* image;
	unsigned int numPix = getNumPixels(myFile);
	image = malloc((sizeof(pixel)) * (numPix));
	if (image == NULL) {
		perror("error allocating memory (input/makePixelArray)");
		exit(-1);
	}

	fseek(myFile, getStart(myFile), SEEK_SET);

	unsigned int arraySize = rowSize * height;
	unsigned int i = 0, whichByte = 0;
	while(whichByte < arraySize) {
		if ((whichByte % rowSize) < (width * 3)) {
			image[i].blu = fgetc(myFile);
			image[i].grn = fgetc(myFile);
			image[i].red = fgetc(myFile);
			image[i].tot_rgb = image[i].blu + image[i].grn + image[i].red;
			whichByte += 3;
			i++;
		} else {
			fseek(myFile, paddingLen, SEEK_CUR);
			whichByte += paddingLen;

		}
	}

	return image;
}
