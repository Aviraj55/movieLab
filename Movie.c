/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"
#include "ImageList.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *newMovie = NULL;
	newMovie = malloc(sizeof(MOVIE));
	newMovie->Frames = CreateImageList();
	
	return newMovie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie);
	DeleteImageList(movie->Frames);
	movie->Frames = NULL;
	free(movie);

}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{

	assert(movie);
	assert(movie->Frames->First->YUVImage);
	IENTRY *currentImageNode = NULL, *next = NULL;
	currentImageNode = movie->Frames->First;

	while(currentImageNode)
	{
		next = currentImageNode->Next;
		
		for(int x = 0; x < currentImageNode->YUVImage->W; x++)
		{
			for(int y = 0; y < currentImageNode->YUVImage->H; y++)	
			{
				int C = GetPixelY(currentImageNode->YUVImage, x, y) -16;
				int D = GetPixelU(currentImageNode->YUVImage, x, y) - 128;
				int E = GetPixelV(currentImageNode->YUVImage, x, y) - 128;

				int R, G, B, tempR, tempG, tempB;

				tempR = ((298 * C + 409 * E + 128) >> 8);
				tempG = ((298 * C - 100 * D - 208 * E + 128) >> 8);
				tempB = ((298 * C + 516 * D + 128) >> 8);

				R = (tempR < 0) ? 0 : (tempR > 255) ? 255: tempR; 
				G = (tempG < 0) ? 0 : (tempG > 255) ? 255: tempG; 
				B = (tempB < 0) ? 0 : (tempB > 255) ? 255: tempB;

				SetPixelR(currentImageNode->RGBImage, x, y, R);
				SetPixelG(currentImageNode->RGBImage, x, y, G);
				SetPixelB(currentImageNode->RGBImage, x, y, B);

			}
		}
		DeleteYUVImage(currentImageNode->YUVImage);	
		currentImageNode->YUVImage = NULL;
		currentImageNode = next;
	}
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	assert(movie->Frames->First->RGBImage);

	IENTRY *currentImageNode = NULL, *next = NULL;
       	currentImageNode = movie->Frames->First;

	while(currentImageNode)
	{
		next = currentImageNode->Next;
		
		YUVIMAGE *currentYUVImage = NULL;	
		currentYUVImage = CreateYUVImage(currentImageNode->RGBImage->W, currentImageNode->RGBImage->H);
		currentImageNode->YUVImage = currentYUVImage;		

	
		for(int x = 0; x < currentImageNode->RGBImage->W; x++)
		{
			for(int y = 0; y < currentImageNode->RGBImage->H; y++)
			{
				int Y, U, V, tempY, tempU, tempV;
				unsigned char R, G, B;
				R = GetPixelR(currentImageNode->RGBImage, x, y);	
				G = GetPixelG(currentImageNode->RGBImage, x, y);
				B = GetPixelB(currentImageNode->RGBImage, x, y);

				tempY = ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16; 
				
				tempU = ((-38 * R - 74  * G + 128 * B + 128) >> 8) + 128;

				tempV = ((112 * R - 94  * G - 18 * B + 128) >> 8) + 128;

				Y = (tempY < 0) ? 0 : (tempY > 255) ? 255: tempY;
				U = (tempU < 0) ? 0 : (tempU > 255) ? 255: tempU;
				V = (tempV < 0) ? 0 : (tempV > 255) ? 255: tempV;

				SetPixelY(currentImageNode->YUVImage, x, y, Y);
				SetPixelU(currentImageNode->YUVImage, x, y, U);
				SetPixelV(currentImageNode->YUVImage, x, y, V);
				
			}
		}
	
		DeleteImage(currentImageNode->RGBImage);
		currentImageNode->RGBImage = NULL;
		currentImageNode = next;
	}
}

int MovieLength(const MOVIE *movie)
{
    return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
    {
        return movie->Frames->First->RGBImage->H;
    }//fi

    else if(movie->Frames->First->YUVImage)
    {
        return movie->Frames->First->YUVImage->H;
    }//fi esle

    else
    return 0;
}

int MovieWidth(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
        {
                return movie->Frames->First->RGBImage->W;
        }//fi

        else if(movie->Frames->First->YUVImage)
        {
                return movie->Frames->First->YUVImage->W;
        }//fi esle

        else
        return 0;
}

/* EOF */
