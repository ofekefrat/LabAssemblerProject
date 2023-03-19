#ifndef label_h
#define label_h

#include "../../root.h"
#define LABEL_ERROR (-1)

/* getLabel: if the label exists in the symbol table (searched by name), returns a pointer to it.
 * otherwise returns null */
Label* getLabel(const char* name, List symbolTable);

/* addLabel: add a label to the symbol table.*/
void addLabel(const char* name, const char* type, int address, List* labels);

/* isUniqueLabelName: returns 1 if the label name is unique and viable, and 0 otherwise. */
int isUniqueLabelName(const char* name, List symbolTable);

#endif
