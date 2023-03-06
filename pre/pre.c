#include "pre.h"

FILE* preAssemble(FILE* source, const char* oldFileName) {

    int r;
    char line[MAX_LINE_LENGTH];
    char newFileName[MAX_FILE_NAME];
    Macro *macros[MAX_MACROS] = { NULL };

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
//    freeUnusedMemory(macros);
    return output;
}

int isDef(const char* line) {
    if (strlen(line) < 4 || line[0] != 'm' || line[1] != 'c' || line[2] != 'r' || line[3] != ' ')
        return 0;

    return 1;
}

//TODO Verify & allow macro spreads inside labels
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

void printFileContent(FILE* file) {
    char line[MAX_LINE_LENGTH];
    rewind(file);
    while (fgets(line, MAX_LINE_LENGTH, file)) { // fgets, not EOF
        printf("%s", line);
    }
}
