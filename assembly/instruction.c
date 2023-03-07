#include "assembly.h"

void addInstruction(const char *line, int *ind, int opcode, Word *instructionArray, Label **symbolTable) {
    Word sourceOperand, destOperand, instruction;
    char operand1[MAX_LABELS], operand2[MAX_LABELS];
    Label* pLabel;
    int *pInt = NULL, i = *ind, regSrc = reg << SOURCE_AM_IND , regDest = reg << DEST_AM_IND;
    memset(operand1, 0, MAX_LABELS);
    memset(operand2, 0, MAX_LABELS);

    instruction.value = opcode << OPCODE_IND;

    /* source operand*/
    skipWhiteSpaces(line, &i);
    if ((opcode >= mov && opcode <= sub) || opcode == lea) {
        readNextOperand(line, &i, operand1);
        if (operand1[0] == 0) { /* no operands */
            printError("not enough operands");
        }

        /* immediate number operand */
        else if (operand1[0] == '#') {
            if (opcode == lea)
                printError("Illegal operand for operation");
            else { /* not lea, operand is legal */
                readNextNumber(line, &i, pInt);
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
        else if (isRegisterOperand(operand1)) {
            if (opcode == lea)
                printError("Illegal operand for operation");
            else instruction.value |= regSrc;
        }

        /* ADDRESSING METHOD 2? */
//        else if () {}

        /* label operand */
        else {
            pLabel = getLabel(operand1, symbolTable);
            instruction.value |= label << SOURCE_AM_IND;
            if (pLabel != NULL) {
                sourceOperand.value = (!strcmp(pLabel->type, "external")) ? ext << SOURCE_AM_IND : reloc << SOURCE_AM_IND;
                sourceOperand.value |= pLabel->value << 2;
            }
            else sourceOperand.value = immediate; /* to identify later */
        } /* end of label operand */

        if (!verifyComma(line, &i)) {
            printError("Missing comma");
        }
    } /* end of source operand */

    /* destination operand */
    skipWhiteSpaces(line, &i);
    if (opcode < rts) {
        readNextOperand(line, &i, operand2);
        if (operand2[0] == 0) { /* no operands */
            printError("not enough operands");
        }

        /* immediate number */
        else if (operand2[0] == '#') {
            if (opcode == cmp || opcode == prn) {
                readNextNumber(line, &i, pInt);
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
        else if (isRegisterOperand(operand2)) {
            instruction.value |= regDest;
        }

        /* address method 2*/
//        else if() {}

        /* label */
        else {
            pLabel = getLabel(operand1, symbolTable);
            instruction.value |= label << DEST_AM_IND;
            if (pLabel != NULL) {
                destOperand.value = (!strcmp(pLabel->type, "external")) ? ext << DEST_AM_IND : reloc << DEST_AM_IND;
                destOperand.value |= pLabel->value << 2;
            }
            else destOperand.value = immediate;
        }
    } /* end of destination operand */

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
    return (*ind < strlen(line) && line[*ind] != ' ' && line[*ind] != '\t');
}



