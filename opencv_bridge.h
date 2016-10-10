#ifndef OPENCVBRIDGE_H
#define OPENCVBRIDGE_H


#include <opencv/cv.h>

void IplImageToBuffer(IplImage* iImage, unsigned char* buffer) ;
void BufferToIplImage(unsigned char* buffer, IplImage* iImage) ;


#endif
