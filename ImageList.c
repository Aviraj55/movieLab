/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2020                   */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
	IENTRY *imageEntry = NULL;
	imageEntry = malloc(sizeof(IENTRY));
	if(!imageEntry)
	{
		perror("Out of memory!! Aborting...");
		exit(10);
	}	
	imageEntry->List = NULL;
	imageEntry->Next = NULL;
	imageEntry->Prev = NULL;
	imageEntry->RGBImage = NULL;
	imageEntry->YUVImage = NULL;

	return imageEntry;
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
	assert(entry);
	if(entry->RGBImage)
	{
		DeleteImage(entry->RGBImage);
		entry->RGBImage = NULL;
	}

	else
	{
		DeleteYUVImage(entry->YUVImage);
		entry->YUVImage = NULL;
	}

	entry->Next = NULL;
	entry->Prev = NULL;

	free(entry);

}

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *imageList = NULL;
	imageList = malloc(sizeof(ILIST));

	imageList->length = 0;
	imageList->First = NULL;
	imageList->Last = NULL;

	return imageList;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	assert(list);
	IENTRY *current = NULL, *next = NULL;
	current = list->First;
	while(current)
	{
		next = current->Next;
		DeleteImageEntry(current);
		current = next;
	}

	list->length = 0;
	list->Last = NULL;
	list->First = NULL;
	
	free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	assert(list);
	assert(RGBimage);
	IENTRY *newEntry = CreateImageEntry();
	newEntry->List = list;
	newEntry->Next = NULL;
	newEntry->RGBImage = RGBimage;
	if(!(list->First))
	{
		list->First = newEntry;
		newEntry->Prev = NULL;
	}
	else
	{
		list->Last->Next = newEntry;		//set the last entry's "next" of the "old list" equal to the new entry
		newEntry->Prev = list->Last;
	}

	list->Last = newEntry;
	list->length++;

}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	assert(list);
	assert(YUVimage);
	IENTRY *newEntry = CreateImageEntry();
	newEntry->YUVImage = YUVimage;
	newEntry->List = list;
	newEntry->Next = NULL;

	if(!(list->First))
	{
		list->First = newEntry;
		newEntry->Prev = NULL;
			
	}

	else
	{
		list->Last->Next = newEntry;
		newEntry->Prev = list->Last;	
	}

	list->Last = newEntry;
	list->length++;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	assert(list);
	IENTRY *current = NULL, *previousEntry = NULL, *next = NULL;	
	current = list->First;
	while(current)
	{
		next = current->Next;
		current->Next = previousEntry;
		
		previousEntry = current;
		current = next;
	}
	list->First = previousEntry;
}

/* EOF */
