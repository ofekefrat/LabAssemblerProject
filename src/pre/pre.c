#include "pre.h"

/* preAssemble: the pre-assembly stage. identify and replace any macro definitions and usages in the source file. */
FILE* preAssemble(FILE* source, const char* oldFileName) {

    int i;
    Node* r; /* a pointer to be passed from macro identification to spreading */
    char line[MAX_LINE_LENGTH];
    char newFileName[MAX_FILE_NAME];
    char labelName[MAX_LABEL_LENGTH];
    FILE* output; /* for the resulting source file */
    List macros = { NULL, NULL }; /* linked list for macros */

    sprintf(newFileName, "%s.am", oldFileName);

    output = fopen(newFileName, "w+");

    lineCount=0;

    while (fgets(line, MAX_LINE_LENGTH, source)) {
        i=0;
        memset(labelName, 0, MAX_LABEL_LENGTH);
        lineCount++;

        skipWhiteSpaces(line, &i);
        if (line[i] == ';') {
            fputs(line, output);
            continue;
        }

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

    return output;
}

/* freeMacroList: free up any allocated memory used throughout the pre-assembly phase to avoid memory leaks.*/
void freeMacroList(Node* currentNode) {
    if (currentNode == NULL) return;

    freeMacroList(currentNode->next);
    freeLinesList(currentNode->item.macro.lines.head);
    free(currentNode);
}

/* freeLinesList: free up any allocated memory used for lines*/
void freeLinesList(Node* currentLine) {
    if (currentLine == NULL) return;

    freeLinesList(currentLine->next);
    free(currentLine);
}
