#include "phase1.h"

int error=0, lineCount=1;

void phase1(FILE* source, FILE* output, Label** labels, Data** data) {
    int i, j, labelFlag=0;
    char line[MAX_LINE_LENGTH], labelName[MAX_LABEL_LENGTH], word[MAX_TYPE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, source)) {
        if (line[0] == ';') continue;

        i=0;
        if (hasLabel(line)) {
            labelFlag=1;
            getLabelName(labelName, &i, line);
        }

        if (isDirective(line, &i)) {

            j=0;
            for (; i < MAX_TYPE_LENGTH && i < strlen(line) && line[i] != ' ' && line[i] != '\t'; i++) {
                word[j] = line[i];
                j++;
            }

            if (isDataDirective(word)) {
                if (labelFlag)
                    addLabel(labelName, word, labels);
                addData(line, &i, data);
            }

        }
        else if (isEntry(line)) {
            printf("Entry directive inside label, ignoring line\n");
            continue;
        }

        else {

        }
    }

    if (error) {
        printf("Errors found, stopping..\n");
        exit(1);
    }
}

int hasLabel(const char* line) {
    int i;
    for (i=0; i < strlen(line); i++) {
        if (line[i] == ':') {
            if (i <= MAX_LABEL_LENGTH) return 1;
            printError("Label name is too long");
            return 0;
        }
    }
    return 0;
}

int isDirective(const char* line, int* ind) {
    int i = *ind, j=0;
    while (i < strlen(line) && (line[i] == ' ' || line[i] == '\t')) i++;

    if (line[i] == '.') {
        if (strlen(line) == i+1) return 0;
        *ind = ++i;
        return 1;
    }
    return 0;
}

int isDataDirective(const char* word) { return (!strcmp(word, "data")); }
int isStringDirective(const char* word) { return (!strcmp(word, "string")); }
int isExternDirective(const char* word) { return (!strcmp(word, "external")); }
int isEntryDirective(const char* word) { return (!strcmp(word, "entry")); }
