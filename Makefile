#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2020
#
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
FLAGS = -ansi -std=c99 -Wall -g

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for FileIO.o
FileIO.o: FileIO.h FileIO.c Image.h
	gcc -c FileIO.c -o FileIO.o $(FLAGS)
# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h
	gcc -c DIPs.c -o DIPs.o $(FLAGS)
# Target for Image.o
Image.o: Image.h Image.c
	gcc -c Image.c -o Image.o $(FLAGS)
	
# Target for other object files
IterativeFilter.o: IterativeFilter.c IterativeFilter.h Movie.h Image.h 
	gcc $(FLAGS) -c IterativeFilter.c -o IterativeFilter.o

MovieIO.o: MovieIO.c MovieIO.h ImageList.o
	gcc $(FLAGS) -c MovieIO.c -o MovieIO.o

Movie.o: Movie.c Movie.h
	gcc $(FLAGS) -c Movie.c -o Movie.o

ImageList.o: ImageList.c ImageList.h
	gcc $(FLAGS) -c ImageList.c -o ImageList.o
######################### Generate the executable #####################
# Target for MovieLab
MovieLab: FileIO.o DIPs.o Image.o Movie.o IterativeFilter.o ImageList.o MovieIO.o MovieLab.c
	gcc $(FLAGS) MovieLab.c FileIO.o DIPs.o Movie.o Image.o MovieIO.o IterativeFilter.o ImageList.o -lm -o MovieLab

###############################  others  ##############################
# Target for clean
clean: 
	rm *.o MovieLab	bw0.yuv reverse1.yuv reverse2.yuv hue0.yuv 
