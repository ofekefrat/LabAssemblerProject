#include "macro.h"

/* newMacro: an initializer for macros defined by the user in the source file. returns the new macro struct instance. */
Macro newMacro(const char* name) {
    Macro new;
    strcpy(new.name, name);
    new.lines.head = NULL;
    new.lines.tail = NULL;

    return new;
}

/* addMacroToTable: add a macro to the macro table. */
void addMacroToTable(FILE* input, const char* defLine, List* macros) {
    /* It's safe to assume "endmcr" will be present */
    int i;
    char line[MAX_LINE_LENGTH];
    char name[MAX_MACRO_NAME_LENGTH];
    Item tempItem; /* for node creation */

    char* ops[] = OPCODES; /* the list of opcodes, to make sure no predefined keywords are being used as a macro name.*/
    char* dirs[] = DIRECTIVES;
    Node* currentNode = macros->head;

    memset(name, 0, sizeof(name));
    memset(line, 0, sizeof(line));
    getMacroName(defLine, name);

    for (i=0; i < NUM_OF_OPCODES; i++) {
        if (!strcmp(name, ops[i])) {
            printError("Macro has the same name as one of the predefined operation names");
            return;
        }
    }

    for (i=0; i < NUM_OF_DIRECTIVES; i++) {
        if (!strcmp(name, dirs[i])) {
            printError("Macro has the same name as one of the predefined directives");
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
        if (isEndmcr(line)) break;
        strcpy(tempItem.line, line);
        addToList( &macros->tail->item.macro.lines, newNode(tempItem) );
    }
}

/* spreadMacro: replace the macro mentioned in the source file with the lines it defines.*/
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