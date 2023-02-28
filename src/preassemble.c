#include "preassemble.h"

void printFileContent(FILE* file) {
    char line[MAX_LINE_LENGTH];
    rewind(file);
    while (fgets(line, MAX_LINE_LENGTH, file)) { // fgets, not EOF
        printf("%s", line);
    }
}

FILE* preAssemble(FILE* input) {

    int r;
    char line[MAX_LINE_LENGTH];
    Macro *macros[MAX_MACROS] = { NULL };
    FILE* output = fopen("output.txt", "w+");

    while (fgets(line, MAX_LINE_LENGTH, input)) { // fgets, not EOF

        if (isDef(line)) {
            addMacroToTable(input, line, macros);
        }

        else if ( (r = isSpread(macros, line)) ) {
            spreadMacro(output, macros, r-1);
        }
        else if (line[0] != '\n'){
            fputs(line, output);
        }
    }

    freeUnusedMemory(macros);
    return output;
}

int isDef(const char* line) {
    if (strlen(line) < 4 || line[0] != 'm' || line[1] != 'c' || line[2] != 'r' || line[3] != ' ')
        return 0;

    return 1;
}

int isSpread(Macro** macros, const char* line) {
    int i;
    for (i=0; macros[i] != NULL && i < MAX_MACROS; i++) {
        if (!strcmp(macros[i]->name, line)) return i+1;
    }
    return 0;
}

void freeUnusedMemory(Macro** macros) {
    int i;
    for (i=0; macros[i] != NULL && i < MAX_MACROS; i++) {
        free(macros[i]);
    }
}