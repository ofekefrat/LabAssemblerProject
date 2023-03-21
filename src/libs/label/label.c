#include "label.h"

/* newLabel: an initializer for a new label. returns the new label struct instance.*/
Label newLabel(const char* name, const char* type, int address) {
    Label new;

    strcpy(new.name, name);
    strcpy(new.type, type);
    new.value = address;

    return new;
}

/* isUniqueLabelName: returns 1 if the label name is unique and viable, and 0 otherwise. */
int isUniqueLabelName(const char* name, List symbolTable) {
    int i;
    char* ops[] = OPCODES;
    char* dirs[] = DIRECTIVES;
    Node* currentNode = symbolTable.head;

    for (i=0; i < NUM_OF_OPCODES; i++) {
        if (!strcmp(name, ops[i])) {
            printError("Unable to name label after predefined operation name");
            return 0;
        }
    }

    for (i=0; i < NUM_OF_DIRECTIVES; i++) {
        if (!strcmp(name, dirs[i])) {
            printError("Unable to name label after predefined directive");
            return 0;
        }
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

/* addLabel: add a label to the symbol table.*/
void addLabel(const char* name, const char* type, int address, List* symbolTable) {
    Item item;
    item.label = newLabel(name, type, address);
    addToList(symbolTable, newNode(item));
}

/* getLabel: if the label exists in the symbol table (searched by name), returns a pointer to it.
 * otherwise returns null */
Label* getLabel(const char* name, List symbolTable) {
    Node* currentNode = symbolTable.head;

    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.label.name, name)) return &currentNode->item.label;
        currentNode = currentNode->next;
    }

    return NULL;
}