#ifndef preassemble_h
#define preassemble_h

#include "../libraries.h"

#define MAX_MACRO_NAME_LENGTH 74 /* max line length minus "mcr " */
#define MAX_MACRO_LINES 666 //TODO TBD
#define MAX_MACROS 666 //TODO TBD

typedef struct Macro {
    char name[MAX_MACRO_NAME_LENGTH];
    List lines;
}Macro;

FILE* preAssemble(FILE* source, const char* oldFileName);
void printFileContent(FILE*);
void addMacroToTable(FILE*, const char*, List);
void spreadMacro(FILE*, Node* macro);
//void writeLine(FILE*, const char*);
void freeUnusedMemory(List);
Node* isSpread(List, const char*);
int isDef(const char*);

#endif //preassemble_h
