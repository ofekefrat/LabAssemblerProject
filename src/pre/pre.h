#ifndef pre_h
#define pre_h

#include "../root.h"

/* preAssemble: the pre-assembly stage. identify and replace any macro definitions and usages in the source file. */
FILE* preAssemble(FILE* source, const char* oldFileName);

/* freeMacroList: free up any allocated memory used throughout the pre-assembly phase to avoid memory leaks.*/
void freeLinesList(Node* currentLine);

/* freeLinesList: free up any allocated memory used for lines*/
void freeMacroList(Node* currentNode);

#endif
