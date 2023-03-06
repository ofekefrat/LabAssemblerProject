#ifndef phase_1
#define phase_1

#include "../libraries.h"
#include "assembly.h"

Label* getNextEmptyLabel(const char* name, Label** symbolTable);
int getLabelName(char* buffer, int* ind, const char* line);
void addDataLabel(const char* name, Label** labels);
void addExternLabel(const char* name, Label** symbolTable, Label** externalSymbols);
void addEntry(const char* name, Label** symbolTable, Label** entrySymbols);
int isInstruction(const char* word, char** ops);


extern int error;
extern int lineCount;

#endif //phase_1
