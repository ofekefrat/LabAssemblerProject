#ifndef assembly_h
#define assembly_h

#include "../root.h"
#define MAX_MEMORY 255
#define MAX_ENT_LINE (MAX_LABEL_LENGTH + 1 + 3 + 2)
#define MAX_OB_LINE (4 + 1 + WORD_LENGTH + 2)

extern int lineCount;
extern const char* sfn;

/* compile: produce the required files. */
void compile(FILE* source, const char* fileName);

/* phase1: the first phase of assembly. */
void phase1(FILE *source,
            Word *dataArray,
            Word *instructionArray,
            List *symbolTable);

/* phase2: the second phase of assembly. */
void phase2(FILE *source,
            Word *instructionArray,
            List *symbolTable,
            List *externalSymbols,
            List *entrySymbols);

/* makeObFile: make the .ob file. */
void makeObFile(FILE* file, Word* instructionArray, Word* dataArray);

/* initializeWordArray: for initialization of the data and instruction arrays.*/
void initializeWordArray(Word* array, int size, int value);

/* updateDataAddresses: update addresses of data in the memory image to appear after the instructions. */
void updateDataAddresses(List* symbolTable);

/* freeSymbolTable: free allocated memory used for a linked list (specifically for symbolTable) */
void freeSymbolTable(Node* node);

/* makeExtraFile: for creating the ext and ent files. */
void makeExtraFile(FILE* file, List list);

/* getNumberStartInd: get the index in which the address should start appearing (in ext and ent files) */
int getNumberStartInd(List list);

/* setSpaces: place the required amount of spaces in the given buffer. */
void setSpaces(char* spaces, int amount);

#endif
