#ifndef pre_h
#define pre_h

#include "../root.h"

FILE* preAssemble(FILE* source, const char* oldFileName);
void freeUnusedMemory(List);
void printFileContent(FILE*);

#endif //pre_h
