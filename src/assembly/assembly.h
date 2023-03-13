#ifndef assembly_h
#define assembly_h

#include "../root.h"
#define MAX_MEMORY 255
#define MAX_ENT_LINE (MAX_LABEL_LENGTH + 1 + 3 + 2)
#define MAX_OB_LINE (4 + 1 + WORD_LENGTH + 2)

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
void freeSymbolTable(Node* node);
void makeExtraFile(FILE* file, List list);
int getNumberStartInd(List list);
void setSpaces(char* spaces, int amount);

#endif
