#include "pre.h"

FILE* preAssemble(FILE* source, const char* oldFileName) {

    int r;
    char line[MAX_LINE_LENGTH];
    char newFileName[MAX_FILE_NAME];
    List macros = { NULL, NULL };

    sprintf(newFileName, "%s.am", oldFileName);

    FILE* output = fopen(newFileName, "w+");

    while (fgets(line, MAX_LINE_LENGTH, source)) { // fgets, not EOF

        if (line[0] != ';') continue; // the only case where the line should be completely ignored
        if (isDef(line)) {
            addMacroToTable(source, line, macros);
        }

        else if ( (r = isSpread(macros, line)) ) {
            spreadMacro(output, macros, r-1);
        }
        else {
            fputs(line, output);
        }
    }
    freeUnusedMemory(macros);

    if (error) exit(1);
    return output;
}

int isDef(const char* line) {
    if (strlen(line) < 4 || line[0] != 'm' || line[1] != 'c' || line[2] != 'r' || line[3] != ' ')
        return 0;

    return 1;
}

//TODO Verify & allow macro spreads inside labels
Node* isSpread(List macros, const char* line) {

    Node* currentNode = macros.head;
    while (currentNode != NULL) {
        if (!strcmp(currentNode->item.macro.name, line))
            return currentNode;
    }

    return NULL;
}

void freeUnusedMemory(List macros) {
    int i;
    for (i=0; macros[i] != NULL && i < MAX_MACROS; i++) {
        free(macros[i]);
    }
}

void printFileContent(FILE* file) {
    char line[MAX_LINE_LENGTH];
    rewind(file);
    while (fgets(line, MAX_LINE_LENGTH, file)) { // fgets, not EOF
        printf("%s", line);
    }
}
