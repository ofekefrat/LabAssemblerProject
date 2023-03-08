#include "assembly.h"
//TODO Addressing method 2, TESTING
void addInstruction(const char *line, int *ind, int opcode, Word *instructionArray, Label **symbolTable, Label** externalSymbols) {
    Word sourceOperand, destOperand, instruction;
    char operand1[MAX_LABELS], operand2[MAX_LABELS];
    int i = *ind, regSrc = reg << SOURCE_AM_IND , regDest = reg << DEST_AM_IND;

    sourceOperand.value = INST_ERROR;
    destOperand.value = INST_ERROR;

    memset(operand1, 0, MAX_LABELS);
    memset(operand2, 0, MAX_LABELS);

    instruction.value = opcode << OPCODE_IND;

    /* source operand */
    if (twoOps(opcode)) {
        skipWhiteSpaces(line, &i);
        readNextOperand(line, &i, operand1);
        sourceOperand = getSourceOperand(operand1, opcode, instruction, symbolTable, externalSymbols);

        if (!verifyComma(line, &i)) {
            printError("Missing comma");
        }
    }

    /* destination operand */
    if (opcode < rts) {
        skipWhiteSpaces(line, &i);
        readNextOperand(line, &i, operand2);
        destOperand = getSourceOperand(operand2, opcode, instruction, symbolTable, externalSymbols);
    }

    if ((instruction.value & regDest) == regDest) {
        destOperand.value = immediate;
        destOperand.value |= (operand2[1] - '0') << DEST_AM_IND;
        if ((instruction.value & regSrc) == regSrc) {
            destOperand.value |= (operand1[1] - '0') << (DEST_AM_IND+6);
        }
    }
    else if ((instruction.value & regSrc) == regSrc) {
        sourceOperand.value = immediate;
        sourceOperand.value |= (operand1[1] - '0') << (DEST_AM_IND+6);
    }

    *ind = i;
    //TODO fill in blank labels
    instructionArray[instructionCounter++] = instruction;
    if (twoOps(opcode)) {
        if (sourceOperand.value == INST_ERROR) return;
        instructionArray[instructionCounter++] = sourceOperand;
        if (destOperand.value == INST_ERROR) return;
        instructionArray[instructionCounter++] = destOperand;
    }
    else if (opcode < rts) {
        if (destOperand.value == INST_ERROR) return;
        instructionArray[instructionCounter++] = destOperand;
    }



}

int twoOps(int opcode) {
    return ((opcode >= mov && opcode <= sub) || opcode == lea);
}

Word getSourceOperand(const char* operand, int opcode, Word instruction, Label** symbolTable, Label** externalSymbols) {
    Label* pLabel;
    Word sourceOperand;

    int* pInt = NULL, i=0, j=0; /* it's disgusting and get rid of it, you know what you did*/
    sourceOperand.value=INST_ERROR;

    if (operand[0] == 0) { /* no operands */
        printError("not enough operands");
    }
        /* immediate number operand */
    else if (operand[0] == '#') {
        if (opcode == lea)
            printError("Illegal operand for operation");
        else { /* not lea, operand is legal */
            readNextNumber(operand, &i, pInt);
            if (pInt != NULL) {
                if (*pInt < (1 << (WORD_LENGTH-2))) {
                    sourceOperand.value = immediate;
                    sourceOperand.value |= *pInt;
                }
                else printError("number is too big");
            }
        }
    } /* end of immediate number operand*/

        /* register operand */
    else if (isRegisterOperand(operand)) {
        if (opcode == lea)
            printError("Illegal operand for operation");
        else instruction.value |= reg << SOURCE_AM_IND;
    }

        /* ADDRESSING METHOD 2? */
//        else if () {}

        /* label operand */
    else {
        pLabel = getLabel(operand, symbolTable);
        instruction.value |= label << SOURCE_AM_IND;
        if (pLabel != NULL) {
            if (!strcmp(pLabel->type, "external")) {
                sourceOperand.value = ext;
                while (externalSymbols[j] != NULL) j++;
                *externalSymbols[j] = *pLabel;
            }
            else {
                sourceOperand.value = reloc;
            }
            sourceOperand.value |= pLabel->value << 2;
        }
        else sourceOperand.value = immediate; /* to identify later */
    } /* end of label operand */
    return sourceOperand;
}

Word getDestOperand(const char* operand, int opcode, Word instruction, Label** symbolTable, Label** externalSymbols) {
    Label* pLabel;
    Word destOperand;

    int* pInt = NULL, i=0, j=0; /* it's disgusting and get rid of it, you know what you did*/
    destOperand.value=INST_ERROR;

    if (operand[0] == 0) { /* no operands */
        printError("not enough operands");
    }

        /* immediate number */
    else if (operand[0] == '#') {
        if (opcode == cmp || opcode == prn) {
            readNextNumber(operand, &i, pInt);
            if (pInt != NULL) {
                if (*pInt < (1 << (WORD_LENGTH - 2))) {
                    destOperand.value = immediate;
                    destOperand.value |= *pInt << 2;
                }
                else printError("number is too big");
            }
        }
        else
            printError("Illegal operand for operation");
    } /* end of immediate number */

        /* register */
    else if (isRegisterOperand(operand)) {
        instruction.value |= reg << DEST_AM_IND;
    }

        /* address method 2*/
//        else if() {}

        /* label */
    else {
        pLabel = getLabel(operand, symbolTable);
        instruction.value |= label << DEST_AM_IND;
        if (pLabel != NULL) {
            if (!strcmp(pLabel->type, "external")) {
                destOperand.value = ext;
                while (externalSymbols[j] != NULL) j++;
                *externalSymbols[j] = *pLabel;
            }
            else {
                destOperand.value = reloc;
            }
            destOperand.value |= pLabel->value << 2;
        }
        else destOperand.value = immediate;
    }
    return destOperand;
}

int isRegisterOperand(const char* operand) {
    int res;
    if (strlen(operand) > 2 && operand[0] == 'r'/*&& isdigit(operand[1])*/) {
        res = operand[1] - '0';
        if (res <= NUM_OF_REGS) return 1;
    }
    return 0;
}

void readNextOperand(const char *line, int *ind, char* operand) {
    int i = *ind, j=0;
    skipWhiteSpaces(line, &i);
    while (stillInWord(line, &i) && line[i] != ',') operand[j++] = line[i++];
    *ind = i;
}

int stillInWord(const char* line, const int* ind) {
    return (*ind < strlen(line) && line[*ind] != ' ' && line[*ind] != '\t' && line[*ind] != '\n');
}



