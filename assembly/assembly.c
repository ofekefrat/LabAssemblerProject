#include "assembly.h"
//TODO directive (.blank)
//TODO Instruction (actual action)

// ERRORS:
//TODO unrecognized action
//TODO incorrect amount of operands
//TODO incompatible operand type for operation
//TODO oger lo kayam
//TODO labels are defined no more than once

int instructionCounter=0, dataCounter=0;

FILE* assembly(FILE* source) {

    Label *labels[MAX_LABELS] = { NULL };
    Data *data[MAX_DATA] = { NULL };

}