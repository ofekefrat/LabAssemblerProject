#include "pre.h"

Macro newMacro(const char* name) {
    Macro new;
    strcpy(new.name, name);

    return new;
}
//TODO No nested macro definitions
//TODO Macros can't be named after native operation names
//TODO Make sure macro definitions can be inside labels in the manual

/* It's safe to assume "endmcr" will be present */
void addMacroToTable(FILE* input, const char* defLine, List macros) {

    char line[MAX_LINE_LENGTH];
    char name[MAX_MACRO_NAME_LENGTH];
    Item tempItem;
    Node* currentNode = macros.head;

    strcpy(name, defLine+4);

    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.macro.name, name)) { /* checking if the names ARE equal */
            printError("A macro of the same name has already been defined");
        }
        currentNode = currentNode->next;
    }

    tempItem.macro = newMacro(name);
    addToList(macros, newNode(tempItem));

    while (fgets(line, MAX_LINE_LENGTH, input)) { // fgets, not endmcr && not EOF
        if (!strcmp(line, "endmcr\n")) break;
        strcpy(tempItem.line, line);
        addToList( macros.tail->item.macro.lines , tempItem);
    }
}

void spreadMacro(FILE* output, Node* macro) {

    Node* currentLine = macro->item.macro.line;
    while (currentLine != NULL) {
        fputs(currentLine->item.line, output);
        currentLine = currentLine->next;
    }
}
