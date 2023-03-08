#ifndef assembly_h
#define assembly_h

#include "../root.h"
#define RESERVED_SPACE 100


FILE* phase1(FILE* source,
             Word* dataArray,
             Word* instructionArray,
             Label** symbolTable,
             Label** externalSymbols,
             Label** entrySymbols,
             char** ops);


void insertNumber(char* digits, int* j, Word* dataArray);
void resetDigitArray(char* arr, int* j);
#endif //assembly_h
