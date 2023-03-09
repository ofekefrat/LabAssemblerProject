#ifndef label_h
#define label_h

#include "../../root.h"
#define LABEL_ERROR (-1)

Label* getLabel(const char* name, List symbolTable);
void addLabel(const char* name, const char* type, int address, List* labels);
void addEntry(const char* name, List symbolTable, List* entrySymbols); //??
int isUniqueLabelName(const char* name, List symbolTable);

#endif //label_h
