/*********************************************************************/
/* 02/27/20              updated for EECS22 assignment Winter2020    */
/*                                                                   */
/* DIPs.c: source file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include <math.h>

IMAGE *BlackNWhite(IMAGE *image, int percent)			//create a black and white image
{
    assert(image);
    assert(percent <= 100 && percent >= 0);

    int x, y, average;
    float percentage = percent / 100.00;   
    
    for (x = 0; x < image->W; x++)
    {
        for(y = 0; y < image->H; y++)
        {
	    int R_offset, G_offset, B_offset;
	    unsigned char newR, newG, newB;
            average = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
	    R_offset = average - GetPixelR(image, x, y);
	    G_offset = average - GetPixelG(image, x, y);
	    B_offset = average - GetPixelB(image, x, y);

	    newR = (unsigned char) GetPixelR(image, x ,y) + (R_offset * percentage); 
	    newG = (unsigned char) GetPixelG(image, x, y) + (G_offset * percentage);
	    newB = (unsigned char) GetPixelB(image, x, y) + (B_offset * percentage);
	
            SetPixelR(image, x, y, newR);
            SetPixelG(image, x, y, newG);
            SetPixelB(image, x, y, newB);
        }
    }
    return image;
}

IMAGE *HueRotate(IMAGE *image, int percent)					//shift an image's hue
{
    assert(image);
    assert(percent >= 0 && percent <= 100);
    double degree = (percent / 100.00) * 360.00;
    double a, b, r;
    double d = degree * PI / 180.0;
    double tmpr, tmpg, tmpb;

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (int x = 0; x < image->W; x++)
    {   for (int y = 0; y < image->H; y++)
        {
            tmpr = GetPixelR(image, x, y) * a + GetPixelG(image, x, y) * b + GetPixelB(image, x, y) * r;
            tmpg = GetPixelR(image, x, y) * r + GetPixelG(image, x, y) * a + GetPixelB(image, x, y) * b;
            tmpb = GetPixelR(image, x, y) * b + GetPixelG(image, x, y) * r + GetPixelB(image, x, y) * a;

            SetPixelR(image, x, y, (tmpr > MAX_PIXEL)?MAX_PIXEL:(tmpr < 0)?0:tmpr);
            SetPixelG(image, x, y, (tmpg > MAX_PIXEL)?MAX_PIXEL:(tmpg < 0)?0:tmpg);
            SetPixelB(image, x, y, (tmpb > MAX_PIXEL)?MAX_PIXEL:(tmpb < 0)?0:tmpb);
        }
    }
    return image;
}

/* EOF */
