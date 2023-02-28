#ifndef preassemble_h
#define preassemble_h

#include "../main.h"
#include "../libraries.h"

#define MAX_MACRO_NAME_LENGTH 666
#define MAX_MACRO_LINES 666
#define MAX_MACROS 666

typedef struct Macro {
    char name[MAX_MACRO_NAME_LENGTH];
    char lines[MAX_MACRO_LINES][MAX_LINE_LENGTH];
}Macro;

void preassemble(FILE*);
void addMacroToTable(FILE*, const char*, Macro**);
void spreadMacro(FILE*, Macro**, int);
//void writeLine(FILE*, const char*);
void freeUnusedMemory(Macro**);
int isSpread(Macro**, const char*);
int isDef(const char*);

#endif //preassemble_h
