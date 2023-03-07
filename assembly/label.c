#include "phase1.h"
//TODO make cells for labels
Label newLabel(const char* name, const char* type, int address) {

//    Label* temp = (Label*) malloc(sizeof(Label));
    Label new;

    strcpy(new.name, name);
    strcpy(new.type, type);
    new.value = address;

//    temp = new;
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

int readLabelName(char* buffer, int* ind, const char* line) {
    int i = *ind;
    if (!isalpha(line[i])) {
        printError("first character in label name must be alphabetical");
    }
    buffer[0] = line[i];

    for (; i < strlen(line) && line[i] != ':'; i++) {
        if (i < MAX_LABEL_LENGTH) {
            if (!isalnum(line[i])) {
                printError("Only digits and alphabetical character allowed in label name");
                return LABEL_ERROR;
            }
            buffer[i] = line[i];
        }
    }

    if (strlen(buffer) > MAX_LABEL_LENGTH) {
        strcpy(buffer, "error");
    }
    *ind = i;
}

void printError(const char* str) {
    printf("in line %d: %s\n", lineCount, str);
    if (!error) error=1;
}
