/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2020                   */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include <assert.h>
#include <stdio.h>
#include "IterativeFilter.h"

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, int start, int end, int change)
{
	assert(image);
	MOVIE *outputMovie = NULL;		//create the output movie and the list of frames it points to
	outputMovie = CreateMovie();

	if(start < end)
	{
		for(int i = start; i <= end; i += change)
		{
			IMAGE *newImage = NULL;
			newImage = CopyImage(image);
			newImage = filter(newImage, i);
			AppendRGBImage(outputMovie->Frames, newImage);
		}
	
		DeleteImage(image);	
		RGB2YUVMovie(outputMovie);
	}

	else if (end < start)
	{

		for(int j = start; j >= end; j -= change)
		{
			
			IMAGE *newImage = NULL;
			newImage = CopyImage(image);
			newImage = filter(newImage, j);
			AppendRGBImage(outputMovie->Frames, newImage);
		}
		



		DeleteImage(image);
		RGB2YUVMovie(outputMovie);
	}

	return outputMovie;
}
