/*********************************************************************/
/* 02/27/20                                                          */
/* DIPs.h: header file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#ifndef DIPS_H
#define DIPS_H

#include "Image.h"
#include "FileIO.h"

// BlackNWhite filter
IMAGE *BlackNWhite(IMAGE *image, int percent);

// HueRotate filter
IMAGE *HueRotate(IMAGE *image, int percent);

#endif
