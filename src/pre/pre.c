#include "pre.h"

FILE* preAssemble(FILE* source, const char* oldFileName) {

    Node* r;
    int i;
    char line[MAX_LINE_LENGTH];
    char newFileName[MAX_FILE_NAME];
    char labelName[MAX_LABEL_LENGTH];
    FILE* output;
    List macros = { NULL, NULL };

    sprintf(newFileName, "%s.am", oldFileName);

    output = fopen(newFileName, "w+");

    while (fgets(line, MAX_LINE_LENGTH, source)) {
        i=0;
        memset(labelName, 0, MAX_LABEL_LENGTH);

        skipWhiteSpaces(line, &i);
        if (line[i] == ';') continue;

        if (isDef(line)) {
            addMacroToTable(source, line, &macros);
        }

        else if ( (r = isSpread(macros, line, labelName)) ) {
            spreadMacro(output, r, labelName);
        }
        else {
            fputs(line, output);
        }
    }

    freeMacroList(macros.head);

    if (error) exit(1);

    return output;
}

void freeMacroList(Node* currentNode) {
    if (currentNode == NULL) return;

    freeMacroList(currentNode->next);
    freeLinesList(currentNode->item.macro.lines.head);
    free(currentNode);
}

void freeLinesList(Node* currentLine) {
    if (currentLine == NULL) return;

    freeLinesList(currentLine->next);
    free(currentLine);
}

