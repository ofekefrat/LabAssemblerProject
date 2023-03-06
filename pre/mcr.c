#include "pre.h"

Macro newMacro(const char* name) {
//    Macro* temp = (Macro*) malloc(sizeof(Macro));
    Macro new;
    strcpy(new.name, name);
    new.lineCount = 0;
//    *temp = new;

    return new;
}
//TODO No nested macro definitions
//TODO Macros can't be named after native operation names
//TODO Make sure macro definitions can be inside labels in the manual

/* It's safe to assume "endmcr" will be present */
void addMacroToTable(FILE* input, const char* defLine, Macro** macros) {
    int i, j=0;
    char line[MAX_LINE_LENGTH];
    char name[MAX_MACRO_NAME_LENGTH];

    strcpy(name, defLine+4);
    for (i=0; macros[i] != NULL && i < MAX_MACROS; i++) {
        if (!strcmp(macros[i]->name, name)) { /* checking if the names ARE equal */
            printf("redefinition of existing macro\n");
            exit(0);
        }
    }
    *macros[i] = newMacro(name);

    while (j < MAX_MACRO_LINES && fgets(line, MAX_LINE_LENGTH, input)) { // fgets, not endmcr && not EOF
        if (!strcmp(line, "endmcr\n")) break;
        strcpy(macros[i]->lines[j], line);
        macros[i]->lineCount++;
        j++;
    }
}

void spreadMacro(FILE* output, Macro** macros, int macroInd) {
    int i;
    for (i=0; /*macros[macroInd]->lines[i] != NULL*/ i < macros[macroInd]->lineCount && i < MAX_MACRO_LINES; i++) {
        fputs(macros[macroInd]->lines[i], output);
    }
}
