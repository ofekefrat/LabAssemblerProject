#ifndef assembly_h
#define assembly_h

#include "../libraries.h"
#define MAX_LABEL_LENGTH 30 /* not including colon */
#define MAX_TYPE_LENGTH 9

typedef struct InstructionLabel {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int address;
}InstructionLabel;


typedef struct DataLabel {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
    int address;
}DataLabel;

typedef struct ExternalLabel {
    char name[MAX_LABEL_LENGTH];
    char type[MAX_TYPE_LENGTH];
}ExternalLabel;

typedef union Label {
    DataLabel dataLabel;
    ExternalLabel externalLabel;
    InstructionLabel instructionLabel;
}Label;

static int error=0;

#endif //assembly_h
