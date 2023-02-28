#include "preassemble.h"

FILE* preAssemble(FILE* input) {

    int r;
    char line[MAX_LINE_LENGTH];
    Macro *macros[MAX_MACROS] = { NULL };
    FILE* output = fopen("output.exe", "a");

    while (fgets(line, MAX_LINE_LENGTH, input)) { // fgets, not EOF

        if (isDef(line)) {
            addMacroToTable(input, line, macros);
        }

        else if ( (r = isSpread(macros, line)) ) {
            spreadMacro(output, macros, r);
        }
        else {
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
    for (i=0; &macros[i] != NULL && i < MAX_MACROS; i++) {
        if (!strcmp(macros[i]->name, line)) return i;
    }
}

void freeUnusedMemory(Macro** macros) {
    int i;
    for (i=0; &macros[i] != NULL && i < MAX_MACROS; i++) {
        free(macros[i]);
    }
}