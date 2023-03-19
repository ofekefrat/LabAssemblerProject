#ifndef macro_h
#define macro_h

#include "../../root.h"

/* newMacro: an initializer for macros defined by the user in the source file */
void addMacroToTable(FILE* source, const char* defLine, List* macros);

/* spreadMacro: replace the macro mentioned in the source file with the lines it defines.*/
void spreadMacro(FILE* output, Node* macro, const char* labelName);

#endif
