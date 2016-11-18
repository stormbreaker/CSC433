#include <stdio.h>

/*
    This file contains all of the function prototypes for reading images in from
    a .bmp file.  This code was copy and pasted straight from the code provided
    by Dr. Weiss.

    LoadBmpFile is the main function which reads the fil in.  All other functions
    are helper functions.  
*/

bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
static short readShort( FILE* infile );
static int readLong( FILE* infile );
static void skipChars( FILE* infile, int numChars );
static inline int GetNumBytesPerRow( int NumCols );
