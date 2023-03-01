#ifndef preassemble_h
#define preassemble_h

#include "../libraries.h"

#define MAX_MACRO_NAME_LENGTH 74 /* max line length minus "mcr " */
#define MAX_MACRO_LINES 666 //TODO TBD
#define MAX_MACROS 666 //TODO TBD

typedef struct Macro {
    char name[MAX_MACRO_NAME_LENGTH];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
    int lineCount;
}Macro;

FILE* preAssemble(FILE*);
void printFileContent(FILE*);
void addMacroToTable(FILE*, const char*, Macro**);
void spreadMacro(FILE*, Macro**, int);
//void writeLine(FILE*, const char*);
void freeUnusedMemory(Macro**);
int isSpread(Macro**, const char*);
int isDef(const char*);

#endif //preassemble_h
