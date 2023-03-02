#include "phase1.h"

Label* newLabel(const char* name, const char* type, int address) {

    Label* temp = (Label*) malloc(sizeof(Label));
    Label new;

    strcpy(new.name, name);
    strcpy(new.type, type);
    new.address = address;

    *temp = new;
    return temp;
}

void addLabel(const char* name, const char* type, Label** labels) {
    int i;

    for (i=0; i < MAX_LABELS && labels[i] != NULL; i++) {
        if (strcmp("error", name) != 0 && !strcmp(labels[i]->name, name)) {
            printError("Duplicate label name");
        }
    }

    if (!strcmp(type, "entry")) return;
    if (!strcmp(type, "external")) {
        labels[i] = newLabel(name, type, NO_ADDRESS);
    }
    else if (!strcmp(type, "data") || !strcmp(type, "string")) {
        labels[i] = newLabel(name, type, dataCounter);
    }
//    else if instruction...
}

void getLabelName(char* buffer, int* ind, const char* line) {
    int i = *ind;
    if (!isalpha(line[0])) {
        printError("first character in label name must be alphabetical");
    }
    buffer[0] = line[0];

    for (; i < strlen(line) && line[i] != ':'; i++) {
        if (i < MAX_LABEL_LENGTH) {
            if (!isalnum(line[i])) {
                printError("Only digits and alphabetical character allowed in label name");
                strcpy(buffer, "error");
            }
            buffer[i] = line[i];
        }
    }

    if (strlen(buffer) > MAX_LABEL_LENGTH) {
        strcpy(buffer, "error");
    }
    *ind = i;
}

void printError(const char* str) {
    printf("in line %d: %s\n", lineCount, str);
    if (!error) error=1;
}
