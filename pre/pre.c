#include "pre.h"

FILE* preAssemble(FILE* source, const char* oldFileName) {

    Node* r;
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
            spreadMacro(output, r);
        }
        else {
            fputs(line, output);
        }
    }
    freeUnusedMemory(macros);

    if (error) exit(1);
    return output;
}


void freeUnusedMemory(List macros) {
}

void printFileContent(FILE* file) {
    char line[MAX_LINE_LENGTH];
    rewind(file);
    while (fgets(line, MAX_LINE_LENGTH, file)) { // fgets, not EOF
        printf("%s", line);
    }
}
