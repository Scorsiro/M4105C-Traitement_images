// Conversions between IplImage and unsigned char* buffer
// Author: Pascal Bertolino, 2007, GIPSA-Lab

#include "opencv_bridge.h"

//------------------------------------------------------------------------
void IplImageToBuffer(IplImage* iImage, unsigned char* buffer)
//------------------------------------------------------------------------
// Parameters: an existing IplImage and an already allocated buffer
// This function fills the buffer with the pixels of the IplImage
// IPL image are BGR coded instead of RGB
{
	int h, w ;
	unsigned char* source = (unsigned char*)iImage->imageData ;
	unsigned char* saveSource ;
	unsigned char* dest = buffer ;

	if (iImage->nChannels == 1)
	{
		for (h=0; h<iImage->height; h++)
		{
			memcpy(dest, source, iImage->width) ;
			source += iImage->widthStep ;
			dest += iImage->width ;
		}
	}
	else if (iImage->nChannels == 3)
	{
		for (h=0; h<iImage->height; h++)
		{
			saveSource = source ;

			for (w=0; w<iImage->width; w++)
			{
				*(dest++) = *(source+2) ; // copy and change the BGR order
				*(dest++) = *(source+1) ;
				*(dest++) = *source ;
				source+=3 ;
			}
			source = saveSource + iImage->widthStep ;
		}
	}
}

//------------------------------------------------------------------------
void BufferToIplImage(unsigned char* buffer, IplImage* iImage)
//------------------------------------------------------------------------
// Parameters: a buffer storing an image and an already allocated IplImage
// This function fills the IplImage with the pixels of the buffer
{
	int h, w ;
	unsigned char* source = buffer  ;
	char* dest = iImage->imageData ;
	char* saveDest ;

	if (iImage->nChannels == 1)
	{
		for (h=0; h<iImage->height; h++)
		{
			memcpy(dest, source, iImage->width) ;
			source += iImage->width ;
			dest += iImage->widthStep ;
		}
	}
	else if (iImage->nChannels == 3)
	{
		for (h=0; h<iImage->height; h++)
		{
			saveDest = dest ;
			for (w=0; w<iImage->width; w++)
			{
				*(dest++) = *(source+2) ; // copy and change the RGB order
				*(dest++) = *(source+1) ;
				*(dest++) = *source ;
				source+=3 ;
			}
			dest = saveDest + iImage->widthStep ;
		}
	}
}
