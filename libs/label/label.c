#include "label.h"

Label newLabel(const char* name, const char* type, int address) {

    Label new;

    strcpy(new.name, name);
    strcpy(new.type, type);
    new.value = address;

    return new;
}

void addDataLabel(const char* name, Label** symbolTable) {
    Label* pLabel = getNextEmptyLabel(name, symbolTable);
    *pLabel = newLabel(name, "data", dataCounter);
}

void addInstructionLabel(const char* name, Label** symbolTable) {
    Label* pLabel = getNextEmptyLabel(name, symbolTable);
    *pLabel = newLabel(name, "code", instructionCounter);
}

void addExternLabel(const char* name, Label** symbolTable) {
    Label* pLabel = getNextEmptyLabel(name, symbolTable);
    *pLabel = newLabel(name, "external", 0);

}

void addEntry(const char* name, Label** symbolTable, Label** entrySymbols) {
    int i=0, j=0;

    while (strcmp(symbolTable[i]->name, name) != 0 && i < MAX_LABELS) i++;
    while (entrySymbols[j] != NULL) j++;
    if (i < MAX_LABELS)
        *entrySymbols[j] = *symbolTable[i];
    else
        printError("Label not found for entry directive");
}

Label* getLabel(const char* name, Label** symbolTable) {
    int i;
    for (i=0; i < MAX_LABELS && symbolTable[i] != NULL; i++) {
        if (!strcmp(symbolTable[i]->name, name)) {
            return symbolTable[i];
        }
    }
    return NULL;
}

Label* getNextEmptyLabel(const char* name, Label** symbolTable) {
    int i;
    for (i=0; i < MAX_LABELS && symbolTable[i] != NULL; i++) {
        if (!strcmp(symbolTable[i]->name, name)) {
            printError("Duplicate label name");
        }
    }
    return symbolTable[i];
}

