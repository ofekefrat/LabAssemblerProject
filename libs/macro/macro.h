#ifndef macro_h
#define macro_h

#include "../../root.h"
#define MAX_MACRO_NAME_LENGTH 74 /* max line length minus "mcr " */

struct Macro {
    char name[MAX_MACRO_NAME_LENGTH];
    List lines;
};

void addMacroToTable(FILE*, const char*, List);
void spreadMacro(FILE*, Node* macro);

#endif //macro_h
