#ifndef data_h
#define data_h

#include "../../root.h"

#define MAX_DATA 666
#define MAX_DIGITS 4


/* addIntArray: handle the .data directive: read every number in the line and add it to the memory image. */
void addIntArray(char* line, int* ind, Word* dataArray);

/* addString: handle the .string directive: read every character in the string and add it to the memory image. */
void addString(char* line, int* ind, Word* dataArray);

#endif
