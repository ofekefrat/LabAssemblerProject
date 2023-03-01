#include "phase1.h"

void phase1(FILE* source, FILE* output, int* pIC, int* pDC) {
    char line[MAX_LINE_LENGTH];
    Label *labels[MAX_LABELS];

    while (fgets(line, MAX_LINE_LENGTH, source)) {
        if (line[0] == ';') continue;

        if (isLabel(line)) {
            if (isStorageDirective(line)) {

            }

            else if (isExtern(line)) {

            }

            else if (isEntry(line)) {
                printf("Entry directive inside label, ignoring line\n");
                continue;
            }

            else {

            }
        }
    }
}