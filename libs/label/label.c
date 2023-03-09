#include "label.h"

Label newLabel(const char* name, const char* type, int address) {

    Label new;

    strcpy(new.name, name);
    strcpy(new.type, type);
    new.value = address;

    return new;
}

int isUniqueLabelName(const char* name, List symbolTable) {
    int i;
    char* ops[] = OPCODES;
    Node* currentNode = symbolTable.head;

    for (i=0; i < NUM_OF_OPCODES; i++)
        if (!strcmp(name, ops[i])) {
            printError("Unable to name label after existing operation name");
            return 0;
        }

    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.label.name, name)) {
            printError("Label name isn't unique");
            return 1;
        }
        currentNode = currentNode->next;
    }


    return 1;
}

void addLabel(const char* name, const char* type, int address, List* symbolTable) {
    Item item = { .label = newLabel(name, type, address) };
    addToList(symbolTable, newNode(item));
}

Label* getLabel(const char* name, List symbolTable) {
    Node* currentNode = symbolTable.head;

    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.label.name, name)) return &currentNode->item.label;
        currentNode = currentNode->next;
    }

    return NULL;
}