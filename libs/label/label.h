#ifndef label_h
#define label_h

#include "../../root.h"
#define MAX_LABEL_LENGTH 30 /* not including colon */
#define MAX_TYPE_LENGTH 9
#define LABEL_ERROR (-1)

typedef struct Label {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int value;
}Label;


void addInstructionLabel(const char* name, Label** symbolTable);
Label* getLabel(const char* name, Label** symbolTable);
Label* getNextEmptyLabel(const char* name, Label** symbolTable);
void addDataLabel(const char* name, Label** labels);
void addExternLabel(const char* name, Label** symbolTable);
void addEntry(const char* name, Label** symbolTable, Label** entrySymbols); //??



#endif //label_h
