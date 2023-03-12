#ifndef macro_h
#define macro_h

#include "../../root.h"

void addMacroToTable(FILE* source, const char* defLine, List* macros);
void spreadMacro(FILE* output, Node* macro, const char* labelName);

#endif
