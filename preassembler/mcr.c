#include "preassemble.h"

Macro* newMacro(const char* name) {
    Macro* temp = (Macro*) malloc(sizeof(Macro));
    strcpy(temp->name, name);

    return temp;
}

void addMacroToTable(FILE* input, const char* defLine, Macro** macros) {
    int i, j=0;
    char line[MAX_LINE_LENGTH];
    char name[MAX_MACRO_NAME_LENGTH];

    strcpy(name, defLine+4);
    for (i=0; &macros[i] != NULL && i < MAX_MACROS; i++) {
        if (!strcmp(macros[i]->name, name)) { /* checking if the names ARE equal */
            printf("redefinition of existing macro\n");
            exit(0);
        }
    }
    macros[i] = newMacro(name);

    while (j < MAX_MACRO_LINES && fgets(line, MAX_LINE_LENGTH, input)) { // fgets, not endmcr && not EOF
        if (!strcmp(line, "endmcr")) break;
        strcpy(macros[i]->lines[j], line);
        j++;
    }
}

void spreadMacro(FILE* output, Macro** macros, int macroInd) {
    int i;
    for (i=0; macros[macroInd]->lines[i] != NULL && i < MAX_MACRO_LINES; i++) {
        fputs(macros[macroInd]->lines[i], output);
//        writeLine(output, macros[macroInd]->lines[i]);
    }
}

//void writeLine(FILE* output, const char* line) {
//    fputs(line, output);
//    putc('\n', output);
//}