#include "macro.h"

Macro newMacro(const char* name) {
    Macro new;
    strcpy(new.name, name);
    new.lines.head = NULL;
    new.lines.tail = NULL;

    return new;
}

/* It's safe to assume "endmcr" will be present */
void addMacroToTable(FILE* input, const char* defLine, List* macros) {
    int i;
    char line[MAX_LINE_LENGTH];
    char name[MAX_MACRO_NAME_LENGTH];
    Item tempItem;

    char* ops[] = OPCODES;
    Node* currentNode = macros->head;

    strcpy(name, defLine+4);

    for (i=0; i < NUM_OF_OPCODES; i++) {
        if (!strcmp(name, ops[i])) {
            printError("Macro has the same name as one of the predefined operation names");
            return;
        }
    }

    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.macro.name, name)) { /* checking if the names ARE equal */
            printError("A macro of the same name has already been defined");
        }
        currentNode = currentNode->next;
    }

    tempItem.macro = newMacro(name);
    addToList(macros, newNode(tempItem));

    while (fgets(line, MAX_LINE_LENGTH, input)) {
        if (!strcmp(line, "endmcr\n")) break;
        strcpy(tempItem.line, line);
        addToList( &macros->tail->item.macro.lines, newNode(tempItem) );
    }
}

void spreadMacro(FILE* output, Node* macro, const char* labelName) {
    char newLine[MAX_LINE_LENGTH];
    Node* currentLine = macro->item.macro.lines.head;

    if (labelName[0] != 0) {
        sprintf(newLine, "%s: %s\n", labelName, currentLine->item.line);
        fputs(newLine, output);
    }
    else {
        while (currentLine != NULL) {
            fputs(currentLine->item.line, output);
            currentLine = currentLine->next;
        }
    }
}