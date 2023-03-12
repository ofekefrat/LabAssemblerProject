#ifndef pre_h
#define pre_h

#include "../root.h"

FILE* preAssemble(FILE* source, const char* oldFileName);
void freeLinesList(Node* currentLine);
void freeMacroList(Node* currentNode);

#endif
