#ifndef assembly_h
#define assembly_h

#include "../root.h"
#define MAX_MEMORY 255

extern int lineCount;


void compile(FILE* source, const char* oldFileName);
void phase1(FILE* source,
            Word* dataArray,
            Word* instructionArray,
            List* symbolTable);

void phase2(FILE* source,
            Word* instructionArray,
            List* symbolTable,
            List* externalSymbols,
            List* entrySymbols);

void initializeWordArray(Word* array, int size, int value);
void updateDataAddresses(List* symbolTable);
void updateMemoryImage(Word* instructionArray);
void freeSymbolTable(Node* node);

#endif
