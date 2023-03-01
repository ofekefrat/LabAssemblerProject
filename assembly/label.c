#include "assembly.h"

Label* newLabel(const char* name, const char* type, int address) {

    Label* temp = (Label*) malloc(sizeof(Label));
    Label newLabel;

    if (!strcmp(type, "code")) {
        InstructionLabel new;
        strcpy(new.name, name);
        strcpy(new.type, type);
        new.address = address;
        newLabel.instructionLabel = new;
    }
    else if (!strcmp(type, "data")) {
        DataLabel new;
        strcpy(new.name, name);
        strcpy(new.type, type);
        new.address = address;
        newLabel.dataLabel = new;
    }
    else if (!strcmp(type, "external")) {
        ExternalLabel new;
        strcpy(new.name, name);
        strcpy(new.type, type);
        newLabel.externalLabel = new;
    }
    else {
        printf("newLabel received incorrect type\n");
        exit(1);
    }

    *temp = newLabel;
    return temp;
}

void addLabelToTable(int lineCount, const char* line, int* pID, int* pIC, Label** labels) {
    int i=0;
    char name[MAX_LABEL_LENGTH+1];
    char c = line[0];
    if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z') {
        printf("line %d: First character in label name must be alphabetical\n", lineCount);
        if (!error) error=1;
    }
    name[0] = c;

    for (i=1; i < MAX_LABEL_LENGTH+1 && line[i] != ':'; i++) {
        name[i] = line[i];
    }

    if (strlen(name) > MAX_LABEL_LENGTH) {
        printf("line %d: Label %s's name is too long\n", lineCount, name);
        if (!error) error=1;
        strcpy(name, "error");
    }


}

