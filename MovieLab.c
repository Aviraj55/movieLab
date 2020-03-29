/*********************************************************************/
/* MovieLab.c: source file for the main function                     */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{ 
    IMAGE *input = NULL;
    MOVIE *inputMovie = NULL, *outputMovie = NULL;
    int importFlag = 0, numFrames = 0, start = 0, end = 0, step = 0, reverse = 0;
    char resolution[7];
    int frameWidth = 0, frameHeight = 0;

    iterableFilter userFilter = NULL;

    char inputMovieName[SLEN], inputImageName[SLEN], outputFileName[SLEN];

    // loop through each argument for the main function
    for(int n = 0; n < argc; n++)
    {
        // If the user wants to import an image
        if(!strcmp(argv[n], "-i"))
        {
            // If they are at the last argument
            if(n == argc - 1)
            {
                printf("\nPlease provide the name of the image you want to import: ");
		scanf("%s", inputImageName);
		input = LoadImage(inputImageName);
            }

	    else
	    {
            	input = LoadImage(argv[++n]);
	    }

            if(!input)
            {
                printf("\n\tThe image file %s could not be read\n", argv[n]);
                return 1;
            }

            // Let the program know an image has succesfully been imported
            importFlag = 1;
        }


        // If the user wants to import a movie
        else if(!strcmp(argv[n], "-m"))
        {        
		if(n == argc - 1)
	    	{
			printf("\nPlease provide the name of the movie you want to import: ");
			scanf("%s", inputMovieName);
		}

		strcpy(inputMovieName, argv[++n]);

            importFlag = 2;		//tell the program you imported a movie
        }

	else if(!strcmp(argv[n], "-f"))
	{
		if(n == argc - 1)
		{
			printf("Missing entry for number of frames!");
			return 3;
		}

		numFrames = atoi(argv[++n]);	
	}

	else if(!strcmp(argv[n], "-s"))
	{
		if(n == argc - 1)
		{
			printf("\nMissing argument for the resolution of the frame!");
			return 4;
		}


		strcpy(resolution, argv[++n]);
		sscanf(resolution, "%dx%d", &frameWidth, &frameHeight);
			
	}

	else if(!strcmp(argv[n], "-o"))
	{
		if(n == argc - 1)
		{
			printf("\nPlease provide the name of the output file: ");
			scanf("%s", outputFileName);
		}
		else
		{
			strcpy(outputFileName, argv[++n]);
		}

	}
	
	else if(!strcmp(argv[n], "-start"))
	{
		if(n == argc - 1)
		{
			printf("\nPlease provide the start parameter: ");
			scanf("%d", &start);
		}
		else
		{
			start = atoi(argv[++n]);
		}

		if(!(start >= 0 || start <= 100))
		{
			
			printf("\nPlease enter a valid input (0-100) for start: ");
			scanf("%d", &start);
		}

	}
	
	else if(!strcmp(argv[n], "-end"))
	{
		if(n == argc - 1)
		{
			printf("\nPlease provide the end parameter: ");
			scanf("%d", &end);
		}
		else
		{
			end = atoi(argv[++n]);
		}

		if(!(end >= 0 || end <= 100))
		{
			
			printf("\nPlease enter a valid input (0-100) for end: ");
			scanf("%d", &end);
		}
	}

	else if(!strcmp(argv[n], "-step"))
	{
		if(n == argc - 1)
		{
			printf("\nPlease provide the step parameter: ");
			scanf("%d", &step);
		}
		else
		{
			step = atoi(argv[++n]);
		}

		if(!(step >= 0 && step <= 100))
		{
			
			printf("\nPlease enter a valid input (0-100) for step: ");
			scanf("%d", &step);
		}
	}

	else if(!strcmp(argv[n], "-reverse"))
	{
		reverse = 1;
	}

	else if(!strcmp(argv[n], "-bw"))
	{
		userFilter = &BlackNWhite;
	}

	else if(!strcmp(argv[n], "-hue"))
	{
		userFilter = &HueRotate;
	}
        
    }

    if(!importFlag)
    {
        printf("\nNo -i nor -m for input file to read\n");
        return 1;
    }
    else if(importFlag == 1)
    {
	outputMovie = doIterativeFilter(input, userFilter, start, end, step);

	if(reverse == 1)
	{
		ReverseImageList(outputMovie->Frames);
		printf("\n\"Operation Reverse\" is done!\n");
	}

	SaveMovie(outputFileName, outputMovie);
	DeleteMovie(outputMovie);
    }

    else if(importFlag == 2)
    {
    	inputMovie = LoadMovie(inputMovieName, numFrames, frameWidth, frameHeight);
	
	if(!inputMovie)
	{
		printf("\nThe movie file %s cannot be read", inputMovieName);
		return 2;
	}

        if(reverse == 1)
	{
		ReverseImageList(inputMovie->Frames);
		printf("\n\"Operation Reverse\" is done!");
	}

	SaveMovie(outputFileName, inputMovie);
	DeleteMovie(inputMovie);
	
    }
    return 0;
}

/* EOF */
